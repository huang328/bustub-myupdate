//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// aggregation_executor.cpp
//
// Identification: src/execution/aggregation_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#include "execution/executors/aggregation_executor.h"

#include <memory>
#include <vector>

#include "execution/expressions/column_value_expression.h"
#include "execution/expressions/expression_util.h"
#include "execution/expressions/tuple_value_expression.h"
#include "storage/table/tuple.h"

namespace bustub {

AggregationExecutor::AggregationExecutor(ExecutorContext *exec_ctx, const AggregationPlanNode *plan,
                                         std::unique_ptr<AbstractExecutor> &&child)
    : AbstractExecutor(exec_ctx), plan_(plan), child_(std::move(child)), aht_(plan_->GetAggregates(), plan_->GetAggregateTypes()) {}

void AggregationExecutor::Init() {
  // Initialize child executor
  child_->Init();

  // Initialize SimpleAggregationHashTable
  while (child_->Next(&current_tuple_, &current_rid_)) {
    auto key = MakeAggregateKey(&current_tuple_);
    auto value = MakeAggregateValue(&current_tuple_);
    aht_.InsertCombine(key, value);
  }
  aht_iterator_ = aht_.Begin();
}

auto AggregationExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  while (aht_iterator_ != aht_.End()) {
    // Get the next aggregate value
    auto aggregate_value = aht_iterator_.Val();

    // Create the output tuple
    std::vector<Value> values;
    for (const auto &expr : plan_->OutputSchema().GetColumns()) {
      auto col_name = expr.GetColumnName();
      int group_by_idx = plan_->GetGroupByIndex(col_name);
      int aggregate_idx = plan_->GetAggregateIndex(col_name);

      Value value;
      if (group_by_idx != -1) {
        value = aht_iterator_.Key().values[group_by_idx];
      } else if (aggregate_idx != -1) {
        value = aggregate_value->values[aggregate_idx];
      } else if (col_name == "COUNT(*)") {
        value = aggregate_value->GetCountStarAggregate();
      }

      values.emplace_back(value);
    }
    *tuple = Tuple(values, &plan_->OutputSchema());
    ++aht_iterator_;
    return true;
  }
  return false;
}

}  // namespace bustub
