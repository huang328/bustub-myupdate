//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// table_heap.cpp
//
// Identification: src/storage/table/table_heap.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <cassert>
<<<<<<< HEAD

#include "common/logger.h"
#include "fmt/format.h"
=======
#include <mutex>  // NOLINT
#include <utility>

#include "common/config.h"
#include "common/exception.h"
#include "common/logger.h"
#include "common/macros.h"
#include "concurrency/transaction.h"
#include "fmt/format.h"
#include "storage/page/page_guard.h"
#include "storage/page/table_page.h"
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#include "storage/table/table_heap.h"

namespace bustub {

<<<<<<< HEAD
TableHeap::TableHeap(BufferPoolManager *buffer_pool_manager, LockManager *lock_manager, LogManager *log_manager,
                     page_id_t first_page_id)
    : buffer_pool_manager_(buffer_pool_manager),
      lock_manager_(lock_manager),
      log_manager_(log_manager),
      first_page_id_(first_page_id) {}

TableHeap::TableHeap(BufferPoolManager *buffer_pool_manager, LockManager *lock_manager, LogManager *log_manager,
                     Transaction *txn)
    : buffer_pool_manager_(buffer_pool_manager), lock_manager_(lock_manager), log_manager_(log_manager) {
  // Initialize the first table page.
  auto first_page = reinterpret_cast<TablePage *>(buffer_pool_manager_->NewPage(&first_page_id_));
  BUSTUB_ASSERT(first_page != nullptr,
                "Couldn't create a page for the table heap. Have you completed the buffer pool manager project?");
  first_page->Init(first_page_id_, BUSTUB_PAGE_SIZE, INVALID_LSN, log_manager_, txn);
  buffer_pool_manager_->UnpinPage(first_page_id_, true);
}

auto TableHeap::InsertTuple(const Tuple &tuple, RID *rid, Transaction *txn) -> bool {
  if (tuple.size_ + 32 > BUSTUB_PAGE_SIZE) {  // larger than one page size
    txn->SetState(TransactionState::ABORTED);
    return false;
  }

  auto cur_page = static_cast<TablePage *>(buffer_pool_manager_->FetchPage(first_page_id_));
  if (cur_page == nullptr) {
    txn->SetState(TransactionState::ABORTED);
    return false;
  }

  cur_page->WLatch();

  // Insert into the first page with enough space. If no such page exists, create a new page and insert into that.
  // INVARIANT: cur_page is WLatched if you leave the loop normally.
  while (!cur_page->InsertTuple(tuple, rid, txn, lock_manager_, log_manager_)) {
    auto next_page_id = cur_page->GetNextPageId();
    // If the next page is a valid page,
    if (next_page_id != INVALID_PAGE_ID) {
      auto next_page = static_cast<TablePage *>(buffer_pool_manager_->FetchPage(next_page_id));
      next_page->WLatch();
      // Unlatch and unpin the current page.
      cur_page->WUnlatch();
      buffer_pool_manager_->UnpinPage(cur_page->GetTablePageId(), false);
      cur_page = next_page;
    } else {
      // Otherwise we have run out of valid pages. We need to create a new page.
      auto new_page = static_cast<TablePage *>(buffer_pool_manager_->NewPage(&next_page_id));
      // If we could not create a new page,
      if (new_page == nullptr) {
        // Then life sucks and we abort the transaction.
        cur_page->WUnlatch();
        buffer_pool_manager_->UnpinPage(cur_page->GetTablePageId(), false);
        txn->SetState(TransactionState::ABORTED);
        return false;
      }
      // Otherwise we were able to create a new page. We initialize it now.
      new_page->WLatch();
      cur_page->SetNextPageId(next_page_id);
      new_page->Init(next_page_id, BUSTUB_PAGE_SIZE, cur_page->GetTablePageId(), log_manager_, txn);
      cur_page->WUnlatch();
      buffer_pool_manager_->UnpinPage(cur_page->GetTablePageId(), true);
      cur_page = new_page;
    }
  }
  // This line has caused most of us to double-take and "whoa double unlatch".
  // We are not, in fact, double unlatching. See the invariant above.
  cur_page->WUnlatch();
  buffer_pool_manager_->UnpinPage(cur_page->GetTablePageId(), true);
  // Update the transaction's write set.
  txn->GetWriteSet()->emplace_back(*rid, WType::INSERT, Tuple{}, this);
  return true;
}

auto TableHeap::MarkDelete(const RID &rid, Transaction *txn) -> bool {
  // TODO(Amadou): remove empty page
  // Find the page which contains the tuple.
  auto page = reinterpret_cast<TablePage *>(buffer_pool_manager_->FetchPage(rid.GetPageId()));
  // If the page could not be found, then abort the transaction.
  if (page == nullptr) {
    txn->SetState(TransactionState::ABORTED);
    return false;
  }
  // Otherwise, mark the tuple as deleted.
  page->WLatch();
  page->MarkDelete(rid, txn, lock_manager_, log_manager_);
  page->WUnlatch();
  buffer_pool_manager_->UnpinPage(page->GetTablePageId(), true);
  // Update the transaction's write set.
  txn->GetWriteSet()->emplace_back(rid, WType::DELETE, Tuple{}, this);
  return true;
}

auto TableHeap::UpdateTuple(const Tuple &tuple, const RID &rid, Transaction *txn) -> bool {
  // Find the page which contains the tuple.
  auto page = reinterpret_cast<TablePage *>(buffer_pool_manager_->FetchPage(rid.GetPageId()));
  // If the page could not be found, then abort the transaction.
  if (page == nullptr) {
    txn->SetState(TransactionState::ABORTED);
    return false;
  }
  // Update the tuple; but first save the old value for rollbacks.
  Tuple old_tuple;
  page->WLatch();
  bool is_updated = page->UpdateTuple(tuple, &old_tuple, rid, txn, lock_manager_, log_manager_);
  page->WUnlatch();
  buffer_pool_manager_->UnpinPage(page->GetTablePageId(), is_updated);
  // Update the transaction's write set.
  if (is_updated && txn->GetState() != TransactionState::ABORTED) {
    txn->GetWriteSet()->emplace_back(rid, WType::UPDATE, old_tuple, this);
  }
  return is_updated;
}

void TableHeap::ApplyDelete(const RID &rid, Transaction *txn) {
  // Find the page which contains the tuple.
  auto page = reinterpret_cast<TablePage *>(buffer_pool_manager_->FetchPage(rid.GetPageId()));
  BUSTUB_ASSERT(page != nullptr, "Couldn't find a page containing that RID.");
  // Delete the tuple from the page.
  page->WLatch();
  page->ApplyDelete(rid, txn, log_manager_);
  /** Commented out to make compatible with p4; This is called only on commit or delete, which consequently unlocks the
   * tuple; so should be fine */
  // lock_manager_->Unlock(txn, rid);
  page->WUnlatch();
  buffer_pool_manager_->UnpinPage(page->GetTablePageId(), true);
}

void TableHeap::RollbackDelete(const RID &rid, Transaction *txn) {
  // Find the page which contains the tuple.
  auto page = reinterpret_cast<TablePage *>(buffer_pool_manager_->FetchPage(rid.GetPageId()));
  BUSTUB_ASSERT(page != nullptr, "Couldn't find a page containing that RID.");
  // Rollback the delete.
  page->WLatch();
  page->RollbackDelete(rid, txn, log_manager_);
  page->WUnlatch();
  buffer_pool_manager_->UnpinPage(page->GetTablePageId(), true);
}

auto TableHeap::GetTuple(const RID &rid, Tuple *tuple, Transaction *txn, bool acquire_read_lock) -> bool {
  // Find the page which contains the tuple.
  auto page = static_cast<TablePage *>(buffer_pool_manager_->FetchPage(rid.GetPageId()));
  // If the page could not be found, then abort the transaction.
  if (page == nullptr) {
    txn->SetState(TransactionState::ABORTED);
    return false;
  }
  // Read the tuple from the page.
  if (acquire_read_lock) {
    page->RLatch();
  }
  bool res = page->GetTuple(rid, tuple, txn, lock_manager_);
  if (acquire_read_lock) {
    page->RUnlatch();
  }
  buffer_pool_manager_->UnpinPage(rid.GetPageId(), false);
  return res;
}

auto TableHeap::Begin(Transaction *txn) -> TableIterator {
  // Start an iterator from the first page.
  // TODO(Wuwen): Hacky fix for now. Removing empty pages is a better way to handle this.
  RID rid;
  auto page_id = first_page_id_;
  while (page_id != INVALID_PAGE_ID) {
    auto page = static_cast<TablePage *>(buffer_pool_manager_->FetchPage(page_id));
    page->RLatch();
    // If this fails because there is no tuple, then RID will be the default-constructed value, which means EOF.
    auto found_tuple = page->GetFirstTupleRid(&rid);
    page->RUnlatch();
    buffer_pool_manager_->UnpinPage(page_id, false);
    if (found_tuple) {
      break;
    }
    page_id = page->GetNextPageId();
  }
  return {this, rid, txn};
}

auto TableHeap::End() -> TableIterator { return {this, RID(INVALID_PAGE_ID, 0), nullptr}; }
=======
TableHeap::TableHeap(BufferPoolManager *bpm) : bpm_(bpm) {
  // Initialize the first table page.
  auto guard = bpm->NewPageGuarded(&first_page_id_);
  last_page_id_ = first_page_id_;
  auto first_page = guard.AsMut<TablePage>();
  BUSTUB_ASSERT(first_page != nullptr,
                "Couldn't create a page for the table heap. Have you completed the buffer pool manager project?");
  first_page->Init();
}

auto TableHeap::InsertTuple(const TupleMeta &meta, const Tuple &tuple, LockManager *lock_mgr, Transaction *txn,
                            table_oid_t oid) -> std::optional<RID> {
  std::unique_lock<std::mutex> guard(latch_);
  auto page_guard = bpm_->FetchPageWrite(last_page_id_);
  while (true) {
    auto page = page_guard.AsMut<TablePage>();
    if (page->GetNextTupleOffset(meta, tuple) != std::nullopt) {
      break;
    }

    // if there's no tuple in the page, and we can't insert the tuple, then this tuple is too large.
    BUSTUB_ENSURE(page->GetNumTuples() != 0, "tuple is too large, cannot insert");

    page_id_t next_page_id = INVALID_PAGE_ID;
    auto npg = bpm_->NewPage(&next_page_id);
    BUSTUB_ENSURE(next_page_id != INVALID_PAGE_ID, "cannot allocate page");

    page->SetNextPageId(next_page_id);

    auto next_page = reinterpret_cast<TablePage *>(npg->GetData());
    next_page->Init();

    page_guard.Drop();

    // acquire latch here as TSAN complains. Given we only have one insertion thread, this is fine.
    npg->WLatch();
    auto next_page_guard = WritePageGuard{bpm_, npg};

    last_page_id_ = next_page_id;
    page_guard = std::move(next_page_guard);
  }
  auto last_page_id = last_page_id_;

  auto page = page_guard.AsMut<TablePage>();
  auto slot_id = *page->InsertTuple(meta, tuple);

  // only allow one insertion at a time, otherwise it will deadlock.
  guard.unlock();

  if (lock_mgr != nullptr) {
    lock_mgr->LockRow(txn, LockManager::LockMode::EXCLUSIVE, oid, RID{last_page_id, slot_id});
  }

  page_guard.Drop();

  return RID(last_page_id, slot_id);
}

void TableHeap::UpdateTupleMeta(const TupleMeta &meta, RID rid) {
  auto page_guard = bpm_->FetchPageWrite(rid.GetPageId());
  auto page = page_guard.AsMut<TablePage>();
  page->UpdateTupleMeta(meta, rid);
}

auto TableHeap::GetTuple(RID rid) -> std::pair<TupleMeta, Tuple> {
  auto page_guard = bpm_->FetchPageRead(rid.GetPageId());
  auto page = page_guard.As<TablePage>();
  auto [meta, tuple] = page->GetTuple(rid);
  tuple.rid_ = rid;
  return std::make_pair(meta, std::move(tuple));
}

auto TableHeap::GetTupleMeta(RID rid) -> TupleMeta {
  auto page_guard = bpm_->FetchPageRead(rid.GetPageId());
  auto page = page_guard.As<TablePage>();
  return page->GetTupleMeta(rid);
}

auto TableHeap::MakeIterator() -> TableIterator {
  std::unique_lock<std::mutex> guard(latch_);
  auto last_page_id = last_page_id_;
  guard.unlock();

  auto page_guard = bpm_->FetchPageRead(last_page_id);
  auto page = page_guard.As<TablePage>();
  return {this, {first_page_id_, 0}, {last_page_id, page->GetNumTuples()}};
}

auto TableHeap::MakeEagerIterator() -> TableIterator { return {this, {first_page_id_, 0}, {INVALID_PAGE_ID, 0}}; }

void TableHeap::UpdateTupleInPlaceUnsafe(const TupleMeta &meta, const Tuple &tuple, RID rid) {
  auto page_guard = bpm_->FetchPageWrite(rid.GetPageId());
  auto page = page_guard.AsMut<TablePage>();
  page->UpdateTupleInPlaceUnsafe(meta, tuple, rid);
}
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

}  // namespace bustub
