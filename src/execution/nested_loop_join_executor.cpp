//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_loop_join_executor.cpp
//
// Identification: src/execution/nested_loop_join_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_loop_join_executor.h"
#include "binder/table_ref/bound_join_ref.h"
#include "common/exception.h"

namespace bustub {

<<<<<<< HEAD
// &&右值引用无需保留所有权
NestedLoopJoinExecutor::NestedLoopJoinExecutor(ExecutorContext *exec_ctx, const NestedLoopJoinPlanNode *plan,
                                               std::unique_ptr<AbstractExecutor> &&left_executor,
                                               std::unique_ptr<AbstractExecutor> &&right_executor)
    : AbstractExecutor(exec_ctx),
      plan_(plan),
      left_executor_(std::move(left_executor)),
      right_executor_(std::move(right_executor)){
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2022 Fall: You ONLY need to implement left join and inner join.
=======
NestedLoopJoinExecutor::NestedLoopJoinExecutor(ExecutorContext *exec_ctx, const NestedLoopJoinPlanNode *plan,
                                               std::unique_ptr<AbstractExecutor> &&left_executor,
                                               std::unique_ptr<AbstractExecutor> &&right_executor)
    : AbstractExecutor(exec_ctx) {
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2023 Spring: You ONLY need to implement left join and inner join.
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
    throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
}

<<<<<<< HEAD
void NestedLoopJoinExecutor::Init() {
  left_executor_->Init();
  right_executor_->Init();
  initialized_ = true;
}

auto NestedLoopJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  if(!initialized_){
    left_executor_->Next(&left_tuple_, nullptr);
    right_executor_->Next(&right_tuple_, nullptr);
    initialized_ = true;
  }

  while(true){
    if(left_tuple_ == nullptr){
      return false;
    }
  }

  while(true){
    if(right_tuple_ == nullptr){
      right_executor_->Next(&right_tuple_, nullptr);
      if(right_tuple_ == nullptr){
        left_executor_->Next(&left_tuple_, nullptr);
        right_executor_->Init();
        right_executor_->Next(&right_tuple_, nullptr);
        break;
      }
    }
    
    if(plan_->Preducate()->EvaluateJoin(&left_tuple, plan_->LeftOutputSchema(), &right_tuple_,
                                        plan_->RightOutputSchema())
              .GetAs<bool>()){
    *tuple = left_tuple.CombineWith(&right_tuple_, plan_->OutputSchema());
    right_executor_->Next(&right_tuple_, nullptr);
    return true;
  }
  right_executor_->Next(&right_tuple_, nullptr);
}
}


  

=======
void NestedLoopJoinExecutor::Init() { throw NotImplementedException("NestedLoopJoinExecutor is not implemented"); }

auto NestedLoopJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool { return false; }
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

}  // namespace bustub
