//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// delete_executor.h
//
// Identification: src/include/execution/executors/delete_executor.h
//
// Copyright (c) 2015-19, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "execution/executor_context.h"
#include "execution/executors/abstract_executor.h"
#include "execution/plans/delete_plan.h"
#include "storage/table/tuple.h"

namespace bustub {

/**
<<<<<<< HEAD
 * DeleteExecutor executes a delete on a table.
=======
 * DeletedExecutor executes a delete on a table.
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
 * Deleted values are always pulled from a child.
 */
class DeleteExecutor : public AbstractExecutor {
 public:
  /**
   * Construct a new DeleteExecutor instance.
   * @param exec_ctx The executor context
   * @param plan The delete plan to be executed
   * @param child_executor The child executor that feeds the delete
   */
  DeleteExecutor(ExecutorContext *exec_ctx, const DeletePlanNode *plan,
                 std::unique_ptr<AbstractExecutor> &&child_executor);

  /** Initialize the delete */
  void Init() override;

  /**
   * Yield the number of rows deleted from the table.
   * @param[out] tuple The integer tuple indicating the number of rows deleted from the table
   * @param[out] rid The next tuple RID produced by the delete (ignore, not used)
   * @return `true` if a tuple was produced, `false` if there are no more tuples
   *
   * NOTE: DeleteExecutor::Next() does not use the `rid` out-parameter.
   * NOTE: DeleteExecutor::Next() returns true with the number of deleted rows produced only once.
   */
<<<<<<< HEAD
  auto Next(Tuple *tuple, RID *rid) -> bool override;
=======
  auto Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool override;
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

  /** @return The output schema for the delete */
  auto GetOutputSchema() const -> const Schema & override { return plan_->OutputSchema(); };

 private:
  /** The delete plan node to be executed */
  const DeletePlanNode *plan_;
  /** The child executor from which RIDs for deleted tuples are pulled */
  std::unique_ptr<AbstractExecutor> child_executor_;
<<<<<<< HEAD
  /** The table heap to delete from */
  TableHeap *table_heap_;
  /** The indexes to update */
  std::vector<Index *> indexes_;
  /** The number of deleted tuples */
  size_t num_deleted_ = 0;
};

}  // namespace bustub

=======
};
}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
