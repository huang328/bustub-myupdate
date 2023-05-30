#include "execution/executors/topn_executor.h"

namespace bustub {

TopNExecutor::TopNExecutor(ExecutorContext *exec_ctx, const TopNPlanNode *plan,
                           std::unique_ptr<AbstractExecutor> &&child_executor)
<<<<<<< HEAD
    : AbstractExecutor(exec_ctx),
      plan_(plan),
      child_executor_(std::move(child_executor)),
      top_n_elements_(plan->GetComparator()) {}

void TopNExecutor::Init() {
    child_executor_->Init();
    Tuple tuple;
    RID rid;
    size_t limit = plan_->GetLimit();
    while(child_executor_->Next(&tuple, &rid)){
        top_n_elements_.push(tuple);
        if(top_n_elements_.size() > limit){
            top_n_elements_.pop();
        }
    } 
}

auto TopNExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  if (top_n_elements_.empty()) {
    return false;
  }
  *tuple = top_n_elements_.top();
  top_n_elements_.pop();
  return true;
}

=======
    : AbstractExecutor(exec_ctx) {}

void TopNExecutor::Init() { throw NotImplementedException("TopNExecutor is not implemented"); }

auto TopNExecutor::Next(Tuple *tuple, RID *rid) -> bool { return false; }

auto TopNExecutor::GetNumInHeap() -> size_t { throw NotImplementedException("TopNExecutor is not implemented"); };
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

}  // namespace bustub
