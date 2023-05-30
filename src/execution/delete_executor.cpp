//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// delete_executor.cpp
//
// Identification: src/execution/delete_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

<<<<<<< HEAD
#pragma once

=======
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#include <memory>

#include "execution/executors/delete_executor.h"

namespace bustub {

DeleteExecutor::DeleteExecutor(ExecutorContext *exec_ctx, const DeletePlanNode *plan,
                               std::unique_ptr<AbstractExecutor> &&child_executor)
<<<<<<< HEAD
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {}

void DeleteExecutor::Init() {
  // Initialize child executor
  child_executor_->Init();

  // Get table information
  const auto &table_info = exec_ctx_->GetCatalog()->GetTable(plan_->TableOid());
  table_heap_ = table_info->table.GetTableHeap();

  // Get indexes for the table
  const auto &indexes = table_info->indexes;
  for (const auto &index_info : indexes) {
    auto index = index_info->index.get();
    index->SetKeySchema(table_info->schema);
    indexes_.push_back(index);
  }
}

auto DeleteExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool {
  // Delete tuples from table
  while (child_executor_->Next(tuple, rid)) {
    table_heap_->MarkDelete(*rid, exec_ctx_->GetTransaction());
    num_deleted_++;

    // Update indexes
    for (const auto &index : indexes_) {
      index->DeleteEntry(*tuple, *rid, exec_ctx_->GetTransaction());
    }
  }

  // Return number of deleted tuples
  *tuple = Tuple(std::vector<Value>{Value(num_deleted_)}, &GetOutputSchema());
  return false;
}

}  // namespace bustub


=======
    : AbstractExecutor(exec_ctx) {}

void DeleteExecutor::Init() { throw NotImplementedException("DeleteExecutor is not implemented"); }

auto DeleteExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool { return false; }

}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
