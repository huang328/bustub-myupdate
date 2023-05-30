//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// table_iterator.h
//
// Identification: src/include/storage/table/table_iterator.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <cassert>
<<<<<<< HEAD

=======
#include <memory>
#include <utility>

#include "common/macros.h"
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#include "common/rid.h"
#include "concurrency/transaction.h"
#include "storage/table/tuple.h"

namespace bustub {

class TableHeap;

/**
 * TableIterator enables the sequential scan of a TableHeap.
 */
class TableIterator {
  friend class Cursor;

 public:
<<<<<<< HEAD
  TableIterator(TableHeap *table_heap, RID rid, Transaction *txn);

  TableIterator(const TableIterator &other)
      : table_heap_(other.table_heap_), tuple_(new Tuple(*other.tuple_)), txn_(other.txn_) {}

  ~TableIterator() { delete tuple_; }

  inline auto operator==(const TableIterator &itr) const -> bool {
    return tuple_->rid_.Get() == itr.tuple_->rid_.Get();
  }

  inline auto operator!=(const TableIterator &itr) const -> bool { return !(*this == itr); }

  auto operator*() -> const Tuple &;

  auto operator->() -> Tuple *;

  auto operator++() -> TableIterator &;

  auto operator++(int) -> TableIterator;

  auto operator=(const TableIterator &other) -> TableIterator & {
    table_heap_ = other.table_heap_;
    *tuple_ = *other.tuple_;
    txn_ = other.txn_;
    return *this;
  }

 private:
  TableHeap *table_heap_;
  Tuple *tuple_;
  Transaction *txn_;
=======
  DISALLOW_COPY(TableIterator);

  TableIterator(TableHeap *table_heap, RID rid, RID stop_at_rid);
  TableIterator(TableIterator &&) = default;

  ~TableIterator() = default;

  auto GetTuple() -> std::pair<TupleMeta, Tuple>;

  auto GetRID() -> RID;

  auto IsEnd() -> bool;

  auto operator++() -> TableIterator &;

 private:
  TableHeap *table_heap_;
  RID rid_;

  // When creating table iterator, we will record the maximum RID that we should scan.
  // Otherwise we will have dead loops when updating while scanning. (In project 4, update should be implemented as
  // deletion + insertion.)
  RID stop_at_rid_;
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
};

}  // namespace bustub
