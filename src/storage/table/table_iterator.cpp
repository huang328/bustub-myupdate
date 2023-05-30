//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// table_iterator.cpp
//
// Identification: src/storage/table/table_iterator.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <cassert>
<<<<<<< HEAD

=======
#include <optional>

#include "common/config.h"
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#include "common/exception.h"
#include "concurrency/transaction.h"
#include "storage/table/table_heap.h"

namespace bustub {

<<<<<<< HEAD
TableIterator::TableIterator(TableHeap *table_heap, RID rid, Transaction *txn)
    : table_heap_(table_heap), tuple_(new Tuple(rid)), txn_(txn) {
  if (rid.GetPageId() != INVALID_PAGE_ID) {
    if (!table_heap_->GetTuple(tuple_->rid_, tuple_, txn_)) {
      throw bustub::Exception("read non-existing tuple");
    }
  }
}

auto TableIterator::operator*() -> const Tuple & {
  assert(*this != table_heap_->End());
  return *tuple_;
}

auto TableIterator::operator->() -> Tuple * {
  assert(*this != table_heap_->End());
  return tuple_;
}

auto TableIterator::operator++() -> TableIterator & {
  BufferPoolManager *buffer_pool_manager = table_heap_->buffer_pool_manager_;
  auto cur_page = static_cast<TablePage *>(buffer_pool_manager->FetchPage(tuple_->rid_.GetPageId()));
  BUSTUB_ENSURE(cur_page != nullptr, "BPM full");  // all pages are pinned

  cur_page->RLatch();
  RID next_tuple_rid;
  if (!cur_page->GetNextTupleRid(tuple_->rid_,
                                 &next_tuple_rid)) {  // end of this page
    while (cur_page->GetNextPageId() != INVALID_PAGE_ID) {
      auto next_page = static_cast<TablePage *>(buffer_pool_manager->FetchPage(cur_page->GetNextPageId()));
      cur_page->RUnlatch();
      buffer_pool_manager->UnpinPage(cur_page->GetTablePageId(), false);
      cur_page = next_page;
      cur_page->RLatch();
      if (cur_page->GetFirstTupleRid(&next_tuple_rid)) {
        break;
      }
    }
  }
  tuple_->rid_ = next_tuple_rid;

  if (*this != table_heap_->End()) {
    // DO NOT ACQUIRE READ LOCK twice in a single thread otherwise it may deadlock.
    // See https://users.rust-lang.org/t/how-bad-is-the-potential-deadlock-mentioned-in-rwlocks-document/67234
    if (!table_heap_->GetTuple(tuple_->rid_, tuple_, txn_, false)) {
      cur_page->RUnlatch();
      buffer_pool_manager->UnpinPage(cur_page->GetTablePageId(), false);
      throw bustub::Exception("read non-existing tuple");
    }
  }
  // release until copy the tuple
  cur_page->RUnlatch();
  buffer_pool_manager->UnpinPage(cur_page->GetTablePageId(), false);
  return *this;
}

auto TableIterator::operator++(int) -> TableIterator {
  TableIterator clone(*this);
  ++(*this);
  return clone;
=======
TableIterator::TableIterator(TableHeap *table_heap, RID rid, RID stop_at_rid)
    : table_heap_(table_heap), rid_(rid), stop_at_rid_(stop_at_rid) {
  // If the rid doesn't correspond to a tuple (i.e., the table has just been initialized), then
  // we set rid_ to invalid.
  auto page_guard = table_heap_->bpm_->FetchPageRead(rid_.GetPageId());
  auto page = page_guard.As<TablePage>();
  if (rid_.GetSlotNum() >= page->GetNumTuples()) {
    rid_ = RID{INVALID_PAGE_ID, 0};
  }
}

auto TableIterator::GetTuple() -> std::pair<TupleMeta, Tuple> { return table_heap_->GetTuple(rid_); }

auto TableIterator::GetRID() -> RID { return rid_; }

auto TableIterator::IsEnd() -> bool { return rid_.GetPageId() == INVALID_PAGE_ID; }

auto TableIterator::operator++() -> TableIterator & {
  auto page_guard = table_heap_->bpm_->FetchPageRead(rid_.GetPageId());
  auto page = page_guard.As<TablePage>();
  auto next_tuple_id = rid_.GetSlotNum() + 1;

  if (stop_at_rid_.GetPageId() != INVALID_PAGE_ID) {
    BUSTUB_ASSERT(
        /* case 1: cursor before the page of the stop tuple */ rid_.GetPageId() < stop_at_rid_.GetPageId() ||
            /* case 2: cursor at the page before the tuple */
            (rid_.GetPageId() == stop_at_rid_.GetPageId() && next_tuple_id <= stop_at_rid_.GetSlotNum()),
        "iterate out of bound");
  }

  rid_ = RID{rid_.GetPageId(), next_tuple_id};

  if (rid_ == stop_at_rid_) {
    rid_ = RID{INVALID_PAGE_ID, 0};
  } else if (next_tuple_id < page->GetNumTuples()) {
    // that's fine
  } else {
    auto next_page_id = page->GetNextPageId();
    // if next page is invalid, RID is set to invalid page; otherwise, it's the first tuple in that page.
    rid_ = RID{next_page_id, 0};
  }

  page_guard.Drop();

  return *this;
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
}

}  // namespace bustub
