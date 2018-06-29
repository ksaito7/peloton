//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// multi_constraint.h
//
// Identification: src/include/catalog/multi_constraint.h
//
// Copyright (c) 2015-2017, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>
#include <vector>
#include <map>

#include "common/printable.h"
#include "common/internal_types.h"
#include "type/value.h"

namespace peloton {
namespace catalog {

//===--------------------------------------------------------------------===//
// MultiConstraint Class
//===--------------------------------------------------------------------===//

class MultiConstraint : public Printable {
 public:
  MultiConstraint(ConstraintType type, std::string constraint_name)
      : constraint_type_(type), constraint_name_(constraint_name){};

  MultiConstraint(ConstraintType type, std::string constraint_name,
                  std::vector<oid_t> column_ids)
      : constraint_type_(type), constraint_name_(constraint_name) {
    this->column_ids_ = column_ids;
  };

  //===--------------------------------------------------------------------===//
  // ACCESSORS
  //===--------------------------------------------------------------------===//

  ConstraintType GetType() const { return constraint_type_; }

  std::string GetName() const { return constraint_name_; }

  // Get a string representation for debugging
  const std::string GetInfo() const;

  std::vector<oid_t> GetCols() const { return column_ids_; }

  // Serialize this multi-column constraint
  void SerializeTo(SerializeOutput &out) const;

  // Deserialize this multi-column constraint
  static MultiConstraint DeserializeFrom(SerializeInput &in);


 private:
  //===--------------------------------------------------------------------===//
  // MEMBERS
  //===--------------------------------------------------------------------===//

  // The type of constraint
  ConstraintType constraint_type_ = ConstraintType::INVALID;

  // constraints on column set
  std::vector<oid_t> column_ids_;

  // we do not allow duplicate constraint name in single table
  std::string constraint_name_;
};

}  // namespace catalog
}  // namespace peloton
