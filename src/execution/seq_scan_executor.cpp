//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// seq_scan_executor.cpp
//
// Identification: src/execution/seq_scan_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
<<<<<<< HEAD
#pragma once
=======
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

#include "execution/executors/seq_scan_executor.h"

namespace bustub {

<<<<<<< HEAD
SeqScanExecutor::SeqScanExecutor(ExecutorContext *exec_ctx, const SeqScanPlanNode *plan)
    : AbstractExecutor(exec_ctx), plan_(plan), table_heap_(exec_ctx_->GetCatalog()->GetTableHeap(plan_->GetTableOid())) {}

void SeqScanExecutor::Init() {
  // Open the table and initialize the scan
  table_iterator_ = table_heap_->Begin(exec_ctx_->GetTransaction());
}

auto SeqScanExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  // Check if there are more tuples to scan
  if (table_iterator_ == table_heap_->End()) {
    return false;
  }

  // Get the next tuple and its RID
  *tuple = *table_iterator_;
  *rid = table_iterator_->GetRid();

  // Move to the next tuple
  ++table_iterator_;

  return true;
}

}  // namespace bustub

=======
SeqScanExecutor::SeqScanExecutor(ExecutorContext *exec_ctx, const SeqScanPlanNode *plan) : AbstractExecutor(exec_ctx) {}

void SeqScanExecutor::Init() { throw NotImplementedException("SeqScanExecutor is not implemented"); }

auto SeqScanExecutor::Next(Tuple *tuple, RID *rid) -> bool { return false; }

}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
