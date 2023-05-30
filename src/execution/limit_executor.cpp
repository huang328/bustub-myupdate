//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// limit_executor.cpp
//
// Identification: src/execution/limit_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/limit_executor.h"

namespace bustub {

LimitExecutor::LimitExecutor(ExecutorContext *exec_ctx, const LimitPlanNode *plan,
                             std::unique_ptr<AbstractExecutor> &&child_executor)
<<<<<<< HEAD
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)), num_tuples_produced_(0) {}

void LimitExecutor::Init() {
    child_executor_->Init();
}

auto LimitExecutor::Next(Tuple *tuple, RID *rid) -> bool { 
    if(num_tuples_produced_ >= plan_->GetLimit()){
        return false;
    }

    if(child_executor_->Next(tuple, rid)){
        num_tuples_produced_++;
        return true;
    }

    return false;
}
=======
    : AbstractExecutor(exec_ctx) {}

void LimitExecutor::Init() { throw NotImplementedException("LimitExecutor is not implemented"); }

auto LimitExecutor::Next(Tuple *tuple, RID *rid) -> bool { return false; }
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

}  // namespace bustub
