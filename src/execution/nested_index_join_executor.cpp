//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_index_join_executor.cpp
//
// Identification: src/execution/nested_index_join_executor.cpp
//
// Copyright (c) 2015-19, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_index_join_executor.h"

namespace bustub {

<<<<<<< HEAD
NestIndexJoinExecutor::NestJoinExecutor(ExecutorContext *exec_ctx, const NestedIndexJoinPlanNode *plan,
                                             std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {
  if (plan->GetJoinType() != JoinType::LEFT && plan->GetJoinType() != JoinType::INNER) {
    throw NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
}

void NestIndexJoinExecutor::Init() {
  child_executor_->Init();

  Tuple tuple;
  RID rid;
  while (child_executor_->Next(&tuple, &rid)) {
    outer_tuples_.emplace_back(std::make_pair(tuple, rid));
  }

  outer_iter_ = outer_tuples_.begin();
}

bool NestIndexJoinExecutor::Next(Tuple *tuple, RID *rid) {
  while (true) {
    if (outer_iter_ == outer_tuples_.end()) {
      return false;
    }

    const auto &outer_tuple = outer_iter_->first;
    const auto &_rid = outer_iter_->second;

    std::vector<Value> key_values;
    for (const auto &expr : plan_->GetKeyExprs()) {
      key_values.emplace_back(expr->Evaluate(&outer_tuple, plan_->OuterTableSchema()).Copy());
    }
    Tuple key_tuple{key_values, plan_->InnerTableSchema()};

    std::vector<RID> rids;
    plan_->GetIndex()->ScanKey(key_tuple, &rids, exec_ctx_->GetTransaction());

    for (const auto &inner_rid : rids) {
      Tuple inner_tuple;
      if (exec_ctx_->GetCatalog()->GetTable(plan_->GetInnerTableOid())->_->GetTuple(inner_rid, &inner_tuple,
                                                                                   exec_ctx_->GetTransaction())) {
        std::vector<Value> values;
        for (const auto &expr : plan_->GetOutputExprs()) {
          if (expr->GetChildAt(0)->GetReturnValueType() == ValueType::kLeftRow) {
            values.emplace_back(Value::Tuple(outer_tuple.GetValues()));
          } else {
            values.emplace_back(expr->Evaluate(&outer_tuple, &inner_tuple, plan_->OuterTableSchema(),
                                               plan_->InnerTableSchema())
                                    .Copy());
          }
        }
        *tuple = Tuple(values, plan_->OutputSchema());
        *rid = outer_rid;
        ++outer_iter_;
        return true;
      }
    }

    ++outer_iter_;
  }
}

}  // namespace bustub

=======
NestIndexJoinExecutor::NestIndexJoinExecutor(ExecutorContext *exec_ctx, const NestedIndexJoinPlanNode *plan,
                                             std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx) {
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2023 Spring: You ONLY need to implement left join and inner join.
    throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
}

void NestIndexJoinExecutor::Init() { throw NotImplementedException("NestIndexJoinExecutor is not implemented"); }

auto NestIndexJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool { return false; }

}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
