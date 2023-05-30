#include "execution/plans/abstract_plan.h"
#include "optimizer/optimizer.h"

<<<<<<< HEAD
// Note for 2022 Fall: You can add all optimizer rule implementations and apply the rules as you want in this file. Note
// that for some test cases, we force using starter rules, so that the configuration here won't take effects. Starter
// rule can be forcibly enabled by `set force_optimizer_starter_rule=yes`.
=======
// Note for 2023 Spring: You can add all optimizer rule implementations and apply the rules as you want in this file.
// Note that for some test cases, we force using starter rules, so that the configuration here won't take effects.
// Starter rule can be forcibly enabled by `set force_optimizer_starter_rule=yes`.
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

namespace bustub {

auto Optimizer::OptimizeCustom(const AbstractPlanNodeRef &plan) -> AbstractPlanNodeRef {
  auto p = plan;
  p = OptimizeMergeProjection(p);
  p = OptimizeMergeFilterNLJ(p);
<<<<<<< HEAD
  p = OptimizeNLJAsIndexJoin(p);
  // p = OptimizeNLJAsHashJoin(p);  // Enable this rule after you have implemented hash join.
=======
  p = OptimizeNLJAsHashJoin(p);
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
  p = OptimizeOrderByAsIndexScan(p);
  p = OptimizeSortLimitAsTopN(p);
  return p;
}

}  // namespace bustub
