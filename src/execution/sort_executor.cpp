#include "execution/executors/sort_executor.h"

namespace bustub {

SortExecutor::SortExecutor(ExecutorContext *exec_ctx, const SortPlanNode *plan,
                           std::unique_ptr<AbstractExecutor> &&child_executor)
<<<<<<< HEAD
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)), current_pos_(0) {}

void SortExecutor::Init() {
  // Initialize the child executor
  child_executor_->Init();

  // Extract the sort direction (desc or asc)
  sort_direction_ = plan_->GetSortDirection();

  // Create a custom comparator based on the sort direction and order by columns
  comparator_ = [this](const Tuple &a, const Tuple &b) {
    for (const auto &order_by : plan_->GetOrderBy()) {
      const auto &col = order_by.first;
      const auto &type = col.GetExpr()->GetReturnValueType();
      const auto &a_val = a.GetValue(plan_->OutputSchema(), col);
      const auto &b_val = b.GetValue(plan_->OutputSchema(), col);

      if (a_val != b_val) {
        return (sort_direction_ == SortDirection::Asc) ? a_val < b_val : a_val > b_val;
      }
    }
    return false;
  };

  // Retrieve all tuples from the child executor and store them in the tuples_ vector
  Tuple tuple;
  RID rid;
  while (child_executor_->Next(&tuple, &rid)) {
    tuples_.emplace_back(tuple);
  }

  // Sort the tuples_ vector using the custom comparator
  std::sort(tuples_.begin(), tuples_.end(), comparator_);
}

auto SortExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  // Check if there are more tuples to return
  if (current_pos_ < tuples_.size()) {
    // Set the output tuple and RID
    *tuple = tuples_[current_pos_];
    *rid = tuple->GetRid();

    // Increment the current position
    current_pos_++;

    return true;
  }

  // No more tuples to return
  return false;
}
=======
    : AbstractExecutor(exec_ctx) {}

void SortExecutor::Init() { throw NotImplementedException("SortExecutor is not implemented"); }

auto SortExecutor::Next(Tuple *tuple, RID *rid) -> bool { return false; }
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

}  // namespace bustub
