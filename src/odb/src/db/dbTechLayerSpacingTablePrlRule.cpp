// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020-2025, The OpenROAD Authors

// Generator Code Begin Cpp
#include "dbTechLayerSpacingTablePrlRule.h"

#include <cstdint>
#include <cstring>

#include "dbDatabase.h"
#include "dbTable.h"
#include "dbTable.hpp"
#include "dbTechLayer.h"
#include "odb/db.h"
namespace odb {
template class dbTable<_dbTechLayerSpacingTablePrlRule>;

bool _dbTechLayerSpacingTablePrlRule::operator==(
    const _dbTechLayerSpacingTablePrlRule& rhs) const
{
  if (flags_.wrong_direction_ != rhs.flags_.wrong_direction_) {
    return false;
  }
  if (flags_.same_mask_ != rhs.flags_.same_mask_) {
    return false;
  }
  if (flags_.exceept_eol_ != rhs.flags_.exceept_eol_) {
    return false;
  }
  if (eol_width_ != rhs.eol_width_) {
    return false;
  }

  return true;
}

bool _dbTechLayerSpacingTablePrlRule::operator<(
    const _dbTechLayerSpacingTablePrlRule& rhs) const
{
  return true;
}

_dbTechLayerSpacingTablePrlRule::_dbTechLayerSpacingTablePrlRule(
    _dbDatabase* db)
{
  flags_ = {};
  eol_width_ = 0;
}

dbIStream& operator>>(dbIStream& stream, _dbTechLayerSpacingTablePrlRule& obj)
{
  uint32_t flags_bit_field;
  stream >> flags_bit_field;
  static_assert(sizeof(obj.flags_) == sizeof(flags_bit_field));
  std::memcpy(&obj.flags_, &flags_bit_field, sizeof(flags_bit_field));
  stream >> obj.eol_width_;
  stream >> obj.length_tbl_;
  stream >> obj.width_tbl_;
  stream >> obj.spacing_tbl_;
  stream >> obj.influence_tbl_;
  // User Code Begin >>
  stream >> obj._within_tbl;
  // User Code End >>
  return stream;
}

dbOStream& operator<<(dbOStream& stream,
                      const _dbTechLayerSpacingTablePrlRule& obj)
{
  uint32_t flags_bit_field;
  static_assert(sizeof(obj.flags_) == sizeof(flags_bit_field));
  std::memcpy(&flags_bit_field, &obj.flags_, sizeof(obj.flags_));
  stream << flags_bit_field;
  stream << obj.eol_width_;
  stream << obj.length_tbl_;
  stream << obj.width_tbl_;
  stream << obj.spacing_tbl_;
  stream << obj.influence_tbl_;
  // User Code Begin <<
  stream << obj._within_tbl;
  // User Code End <<
  return stream;
}

void _dbTechLayerSpacingTablePrlRule::collectMemInfo(MemInfo& info)
{
  info.cnt++;
  info.size += sizeof(*this);

  // User Code Begin collectMemInfo
  info.children_["length_tbl"].add(length_tbl_);
  info.children_["width_tbl"].add(width_tbl_);
  MemInfo& spacing_info = info.children_["spacing_tbl"];
  for (const auto& s : spacing_tbl_) {
    spacing_info.add(s);
  }
  info.children_["influence_tbl"].add(influence_tbl_);
  info.children_["within_tbl"].add(_within_tbl);
  // User Code End collectMemInfo
}

////////////////////////////////////////////////////////////////////
//
// dbTechLayerSpacingTablePrlRule - Methods
//
////////////////////////////////////////////////////////////////////

void dbTechLayerSpacingTablePrlRule::setEolWidth(int eol_width)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  obj->eol_width_ = eol_width;
}

int dbTechLayerSpacingTablePrlRule::getEolWidth() const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  return obj->eol_width_;
}

void dbTechLayerSpacingTablePrlRule::setWrongDirection(bool wrong_direction)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  obj->flags_.wrong_direction_ = wrong_direction;
}

bool dbTechLayerSpacingTablePrlRule::isWrongDirection() const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  return obj->flags_.wrong_direction_;
}

void dbTechLayerSpacingTablePrlRule::setSameMask(bool same_mask)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  obj->flags_.same_mask_ = same_mask;
}

bool dbTechLayerSpacingTablePrlRule::isSameMask() const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  return obj->flags_.same_mask_;
}

void dbTechLayerSpacingTablePrlRule::setExceeptEol(bool exceept_eol)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  obj->flags_.exceept_eol_ = exceept_eol;
}

bool dbTechLayerSpacingTablePrlRule::isExceeptEol() const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;

  return obj->flags_.exceept_eol_;
}

// User Code Begin dbTechLayerSpacingTablePrlRulePublicMethods

uint _dbTechLayerSpacingTablePrlRule::getWidthIdx(const int width) const
{
  auto pos = --(std::lower_bound(width_tbl_.begin(), width_tbl_.end(), width));
  return std::max(0, (int) std::distance(width_tbl_.begin(), pos));
}

uint _dbTechLayerSpacingTablePrlRule::getLengthIdx(const int length) const
{
  auto pos
      = --(std::lower_bound(length_tbl_.begin(), length_tbl_.end(), length));
  return std::max(0, (int) std::distance(length_tbl_.begin(), pos));
}

void dbTechLayerSpacingTablePrlRule::setTable(
    std::vector<int> width_tbl,
    std::vector<int> length_tbl,
    std::vector<std::vector<int>> spacing_tbl,
    std::map<uint, std::pair<int, int>> excluded_map)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  obj->width_tbl_ = width_tbl;
  obj->length_tbl_ = length_tbl;
  for (const auto& spacing : spacing_tbl) {
    dbVector<int> tmp;
    tmp = spacing;
    obj->spacing_tbl_.push_back(tmp);
  }
  obj->_within_tbl = excluded_map;
}

void dbTechLayerSpacingTablePrlRule::getTable(
    std::vector<int>& width_tbl,
    std::vector<int>& length_tbl,
    std::vector<std::vector<int>>& spacing_tbl,
    std::map<uint, std::pair<int, int>>& excluded_map)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  width_tbl = obj->width_tbl_;
  length_tbl = obj->length_tbl_;
  excluded_map = obj->_within_tbl;
  for (const auto& spacing : obj->spacing_tbl_) {
    spacing_tbl.push_back(spacing);
  }
}

void dbTechLayerSpacingTablePrlRule::setSpacingTableInfluence(
    std::vector<std::tuple<int, int, int>> influence_tbl)
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  obj->influence_tbl_ = influence_tbl;
}

dbTechLayerSpacingTablePrlRule* dbTechLayerSpacingTablePrlRule::create(
    dbTechLayer* _layer)
{
  _dbTechLayer* layer = (_dbTechLayer*) _layer;
  _dbTechLayerSpacingTablePrlRule* newrule
      = layer->spacing_table_prl_rules_tbl_->create();
  return ((dbTechLayerSpacingTablePrlRule*) newrule);
}

dbTechLayerSpacingTablePrlRule*
dbTechLayerSpacingTablePrlRule::getTechLayerSpacingTablePrlRule(
    dbTechLayer* inly,
    uint dbid)
{
  _dbTechLayer* layer = (_dbTechLayer*) inly;
  return (dbTechLayerSpacingTablePrlRule*)
      layer->spacing_table_prl_rules_tbl_->getPtr(dbid);
}

void dbTechLayerSpacingTablePrlRule::destroy(
    dbTechLayerSpacingTablePrlRule* rule)
{
  _dbTechLayer* layer = (_dbTechLayer*) rule->getImpl()->getOwner();
  dbProperty::destroyProperties(rule);
  layer->spacing_table_prl_rules_tbl_->destroy(
      (_dbTechLayerSpacingTablePrlRule*) rule);
}

int dbTechLayerSpacingTablePrlRule::getSpacing(const int width,
                                               const int length) const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  uint rowIdx = obj->getWidthIdx(width);
  uint colIdx = obj->getLengthIdx(length);
  return obj->spacing_tbl_[rowIdx][colIdx];
}

bool dbTechLayerSpacingTablePrlRule::hasExceptWithin(int width) const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  uint rowIdx = obj->getWidthIdx(width);
  return (obj->_within_tbl.find(rowIdx) != obj->_within_tbl.end());
}

std::pair<int, int> dbTechLayerSpacingTablePrlRule::getExceptWithin(
    int width) const
{
  _dbTechLayerSpacingTablePrlRule* obj
      = (_dbTechLayerSpacingTablePrlRule*) this;
  uint rowIdx = obj->getWidthIdx(width);
  return obj->_within_tbl.at(rowIdx);
}

// User Code End dbTechLayerSpacingTablePrlRulePublicMethods
}  // namespace odb
// Generator Code End Cpp
