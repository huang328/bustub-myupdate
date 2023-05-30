#include "optimizer/optimizer.h"

namespace bustub {

auto Optimizer::TraverseAndOptimize(const AbstractPlanNodeRef &plan) -> AbstractPlanNodeRef {
  if (plan->GetChildren().empty()) {
    return plan;
  }

  std::vector<AbstractPlanNodeRef> optimized_children;
  for (const auto &child : plan->GetChildren()) {
    optimized_children.push_back(TraverseAndOptimize(child));
  }
  plan->SetChildren(optimized_children);

  if (plan->GetType() == PlanType::Sort && !plan->GetChildren().empty() &&
      plan->GetChildren()[0]->GetType() == PlanType::Limit) {
    return OptimizeSortLimitAsTopN(plan);
  }

  return plan;
}

auto Optimizer::OptimizeSortLimitAsTopN(const AbstractPlanNodeRef &sort_node) -> AbstractPlanNodeRef {
  auto limit_node = sort_node->GetChildren()[0];
  auto sort_keys = static_cast<const SortPlanNode *>(sort_node.get())->GetSortKeys();
  auto limit = static_cast<const LimitPlanNode *>(limit_node.get())->GetLimit();
  auto offset = static_cast<const LimitPlanNode *>(limit_node.get())->GetOffset();
  auto topn_plan_node = std::make_shared<TopNPlanNode>(sort_keys, limit, offset);

  // Set the child of the new TopNPlanNode to be the child of the original LimitPlanNode
  topn_plan_node->AddChild(limit_node->GetChildren()[0]);

  return topn_plan_node;
}

auto Optimizer::Optimize(const AbstractPlanNodeRef &plan) -> AbstractPlanNodeRef {
  return TraverseAndOptimize(plan);
}

}  // namespace bustub

