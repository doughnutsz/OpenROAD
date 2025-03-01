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

#include "odb.h"
namespace utl {
class Logger;
}
namespace odb {

///
/// When adding a new database object, you must add a dbObjectType enumerator
/// and edit dbObject.cpp and assign an unique "character" code for its
/// database-name.
///
class _dbDatabase;
class dbOStream;
class dbIStream;
class dbObjectPage;
class dbObjectTable;
class _dbObject;

///
/// Steps to add new objects -
///      - add the "name_tbl" entry in dbObject.cpp
///      - add the table entry to the getObjectTable method of the container
///      object.
///
enum dbObjectType
{
  dbDatabaseObj,

  // Design Objects
  dbChipObj,
  dbGdsLibObj,
  dbBlockObj,
  dbInstHdrObj,
  dbInstObj,
  dbNetObj,
  dbBTermObj,
  dbITermObj,
  dbBoxObj,
  dbViaObj,
  dbTrackGridObj,
  dbObstructionObj,
  dbBlockageObj,
  dbWireObj,
  dbSWireObj,
  dbSBoxObj,
  dbCapNodeObj,
  dbRSegObj,
  dbCCSegObj,
  dbRowObj,
  dbFillObj,
  dbRegionObj,
  dbHierObj,
  dbBPinObj,
  // Generator Code Begin DbObjectType
  dbAccessPointObj,
  dbBusPortObj,
  dbCellEdgeSpacingObj,
  dbDftObj,
  dbGCellGridObj,
  dbGDSARefObj,
  dbGDSBoundaryObj,
  dbGDSBoxObj,
  dbGDSPathObj,
  dbGDSSRefObj,
  dbGDSStructureObj,
  dbGDSTextObj,
  dbGlobalConnectObj,
  dbGroupObj,
  dbGuideObj,
  dbIsolationObj,
  dbLevelShifterObj,
  dbLogicPortObj,
  dbMarkerObj,
  dbMarkerCategoryObj,
  dbMasterEdgeTypeObj,
  dbMetalWidthViaMapObj,
  dbModBTermObj,
  dbModInstObj,
  dbModITermObj,
  dbModNetObj,
  dbModuleObj,
  dbNetTrackObj,
  dbPolygonObj,
  dbPowerDomainObj,
  dbPowerSwitchObj,
  dbScanChainObj,
  dbScanInstObj,
  dbScanListObj,
  dbScanPartitionObj,
  dbScanPinObj,
  dbTechLayerObj,
  dbTechLayerAreaRuleObj,
  dbTechLayerArraySpacingRuleObj,
  dbTechLayerCornerSpacingRuleObj,
  dbTechLayerCutClassRuleObj,
  dbTechLayerCutEnclosureRuleObj,
  dbTechLayerCutSpacingRuleObj,
  dbTechLayerCutSpacingTableDefRuleObj,
  dbTechLayerCutSpacingTableOrthRuleObj,
  dbTechLayerEolExtensionRuleObj,
  dbTechLayerEolKeepOutRuleObj,
  dbTechLayerForbiddenSpacingRuleObj,
  dbTechLayerKeepOutZoneRuleObj,
  dbTechLayerMaxSpacingRuleObj,
  dbTechLayerMinCutRuleObj,
  dbTechLayerMinStepRuleObj,
  dbTechLayerSpacingEolRuleObj,
  dbTechLayerSpacingTablePrlRuleObj,
  dbTechLayerTwoWiresForbiddenSpcRuleObj,
  dbTechLayerWidthTableRuleObj,
  dbTechLayerWrongDirSpacingRuleObj,
  // Generator Code End DbObjectType

  // Lib Objects
  dbLibObj,
  dbGDSLibObj,
  dbSiteObj,
  dbMasterObj,
  dbMPinObj,
  dbMTermObj,
  dbTechAntennaPinModelObj,

  // Tech Objects
  dbTechObj,
  dbTechViaObj,
  dbTechNonDefaultRuleObj,  // also a design object
  dbTechLayerRuleObj,       // also a design object
  dbTechSameNetRuleObj,
  dbTechLayerSpacingRuleObj,
  dbTechMinCutRuleObj,
  dbTechMinEncRuleObj,
  dbTechV55InfluenceEntryObj,
  dbTechLayerAntennaRuleObj,
  dbTechViaRuleObj,
  dbTechViaGenerateRuleObj,
  dbTechViaLayerRuleObj,

  // Property
  dbPropertyObj,
  dbNameObj
};

class dbDatabase;

class dbObject
{
 public:
  dbObjectType getObjectType() const;
  dbDatabase* getDb() const;
  uint getId() const;
  const char* getTypeName() const;

  static const char* getTypeName(dbObjectType type);
  static dbObjectType getType(const char* name, utl::Logger* logger);
  // These are not intended for client use as the returned class is
  // not exported.  They are for internal db convenience.
  _dbObject* getImpl();
  const _dbObject* getImpl() const;

 protected:
  dbObject() = default;
  ~dbObject() = default;
};

}  // namespace odb
