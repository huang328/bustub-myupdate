//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// index_scan_executor.cpp
//
// Identification: src/execution/index_scan_executor.cpp
//
// Copyright (c) 2015-19, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#pragma once

#include "execution/executors/index_scan_executor.h"

namespace bustub{
IndexScanExecutor::IndexScanExecutor(ExecutorContext *exec_ctx, const IndexScanPlanNode *plan)
    : AbstractExecutor(exec_ctx), plan_(plan) {}

void IndexScanExecutor::Init() {
  auto *index_info = exec_ctx_->GetCatalog()->GetIndex(plan_->GetIndexOid());
  tree_ = dynamic_cast<BPlusTreeIndex<int, RID, int_comparator> *>(index_info->index_.get());
  iter_ = tree_->Begin(plan_->GetLowKey());
  table_heap_ = exec_ctx_->GetCatalog()->GetTable(plan_->GetTableOid())->table_.get();
}

auto IndexScanExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  while (iter_ != tree_->End()) {
    *rid = iter_.->second;
    if (table_heap_->GetTuple(*rid, tuple, exec_ctx_->GetTransaction())) {
      ++iter_;
      return true;
    }
    ++iter_;
  }
  return false;
}

}  // namespace bustub

