//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// insert_executor.cpp
//
// Identification: src/execution/insert_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
<<<<<<< HEAD
#pragma once
=======
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

#include <memory>

#include "execution/executors/insert_executor.h"

namespace bustub {

InsertExecutor::InsertExecutor(ExecutorContext *exec_ctx, const InsertPlanNode *plan,
                               std::unique_ptr<AbstractExecutor> &&child_executor)
<<<<<<< HEAD
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {}

void InsertExecutor::Init() {
  // Initialize child executor
  child_executor_->Init();

  // Get table information
  const auto &table_info = exec_ctx_->GetCatalog()->GetTable(plan_->TableOid());
  table_heap_ = table_info->table.GetTableHeap();
}

auto InsertExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool {
  // Insert tuples into table
  while (child_executor_->Next(tuple, rid)) {
    table_heap_->InsertTuple(*tuple, rid, exec_ctx_->GetTransaction());
    num_inserted_++;
  }

  // Return number of inserted tuples
  *tuple = Tuple(std::vector<Value>{Value(num_inserted_)}, &GetOutputSchema());
  return false;
}

}  // namespace bustub

=======
    : AbstractExecutor(exec_ctx) {}

void InsertExecutor::Init() { throw NotImplementedException("InsertExecutor is not implemented"); }

auto InsertExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool { return false; }

}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
