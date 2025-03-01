///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2019, Nefelus Inc
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <vector>

#include "dbCore.h"
#include "dbVector.h"
#include "odb/ZException.h"
#include "odb/dbIterator.h"
#include "odb/odb.h"

namespace odb {

class dbIStream;
class dbOStream;

class dbTablePage : public dbObjectPage
{
 public:
  char _objects[1];
};

template <class T>
class dbTable : public dbObjectTable, public dbIterator
{
 public:
  // PERSISTANT-DATA
  uint _page_mask;      // bit-mask to get page-offset
  uint _page_shift;     // number of bits to shift to determine page-no
  uint _top_idx;        // largest id which has been allocated.
  uint _bottom_idx;     // smallest id which has been allocated.
  uint _page_cnt;       // high-water mark of page-table
  uint _page_tbl_size;  // length of the page table
  uint _alloc_cnt;      // number of object allocated
  uint _free_list;      // objects on freelist

  // NON-PERSISTANT-DATA
  dbTablePage** _pages;  // page-table

  void resizePageTbl();
  void newPage();
  void pushQ(uint& Q, _dbFreeObject* e);
  _dbFreeObject* popQ(uint& Q);
  void unlinkQ(uint& Q, _dbFreeObject* e);

  dbTable(_dbDatabase* db,
          dbObject* owner,
          dbObjectTable* (dbObject::*m)(dbObjectType),
          dbObjectType type,
          uint page_size = 128,
          uint page_shift = 7);

  // Make a copy of a table.
  // The copy is identical including the ordering of all free-lists.
  // dbTable(_dbDatabase * db, dbObject * owner, const dbTable<T> & T );
  dbTable(_dbDatabase* db, dbObject* owner, const dbTable<T>&);

  ~dbTable() override;

  // returns the number of instances of "T" allocated
  uint size() const { return _alloc_cnt; }

  // Create a "T", calls T( _dbDatabase * )
  T* create();

  // Duplicate a "T", calls T( _dbDatabase *, const T & )
  T* duplicate(T* c);

  // Destroy instance of "T", calls destructor
  void destroy(T*);

  // clear the table
  void clear();

  uint page_size() const { return _page_mask + 1; }

  // Get the object of this id
  T* getPtr(dbId<T> id) const
  {
    uint page = (uint) id >> _page_shift;
    uint offset = (uint) id & _page_mask;

    assert(((uint) id != 0) && (page < _page_cnt));
    T* p = (T*) &(_pages[page]->_objects[offset * sizeof(T)]);
    assert(p->_oid & DB_ALLOC_BIT);
    return p;
  }

  bool validId(dbId<T> id) const
  {
    uint page = (uint) id >> _page_shift;
    uint offset = (uint) id & _page_mask;

    if (((uint) id != 0) && (page < _page_cnt)) {
      T* p = (T*) &(_pages[page]->_objects[offset * sizeof(T)]);
      return (p->_oid & DB_ALLOC_BIT) == DB_ALLOC_BIT;
    }

    return false;
  }

  //
  // Get the object of this id
  // This method is the same as getPtr() but is is
  // use to get objects on the free-list.
  //
  T* getFreeObj(dbId<T> id)
  {
    uint page = (uint) id >> _page_shift;
    uint offset = (uint) id & _page_mask;
    assert(((uint) id != 0) && (page < _page_cnt));
    T* p = (T*) &(_pages[page]->_objects[offset * sizeof(T)]);
    assert((p->_oid & DB_ALLOC_BIT) == 0);
    return p;
  }

  // find the new top_idx...
  void findTop();

  // find the new bottom_idx...
  void findBottom();

  void readPage(dbIStream& stream, dbTablePage* page);
  void writePage(dbOStream& stream, const dbTablePage* page) const;

  bool operator==(const dbTable<T>& rhs) const;
  bool operator!=(const dbTable<T>& table) const;

  // dbIterator interface methods
  bool reversible() override;
  bool orderReversed() override;
  void reverse(dbObject* parent) override;
  uint sequential() override;
  uint size(dbObject* parent) override;
  uint begin(dbObject* parent) override;
  uint end(dbObject* parent) override;
  uint next(uint id, ...) override;
  dbObject* getObject(uint id, ...) override;
  bool validObject(uint id, ...) override { return validId(id); }
  void getObjects(std::vector<T*>& objects);
  void collectMemInfo(MemInfo& info);

 private:
  void copy_pages(const dbTable<T>&);
  void copy_page(uint page_id, dbTablePage* page);
};

template <class T>
dbOStream& operator<<(dbOStream& stream, const dbTable<T>& table);

template <class T>
dbIStream& operator>>(dbIStream& stream, dbTable<T>& table);

// Useful if you want to write the table in a named scope
template <class T>
struct NamedTable
{
  NamedTable(const char* name, const dbTable<T>* table)
      : name(name), table(table)
  {
  }
  const char* name;
  const dbTable<T>* table;
};

template <class T>
dbOStream& operator<<(dbOStream& stream, const NamedTable<T>& named_table);

}  // namespace odb
