#include "binder/bound_order_by.h"
#include "binder/expressions/bound_agg_call.h"
<<<<<<< HEAD
=======
#include "binder/expressions/bound_func_call.h"
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#include "binder/statement/select_statement.h"
#include "binder/table_ref/bound_cte_ref.h"
#include "binder/table_ref/bound_expression_list_ref.h"
#include "binder/table_ref/bound_subquery_ref.h"
#include "common/util/string_util.h"
#include "fmt/format.h"
#include "fmt/ranges.h"

namespace bustub {

<<<<<<< HEAD
=======
auto BoundFuncCall::ToString() const -> std::string { return fmt::format("{}({})", func_name_, args_); }

>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
auto BoundAggCall::ToString() const -> std::string {
  if (is_distinct_) {
    return fmt::format("{}_distinct({})", func_name_, args_);
  }
  return fmt::format("{}({})", func_name_, args_);
}

auto BoundExpressionListRef::ToString() const -> std::string {
  return fmt::format("BoundExpressionListRef {{ identifier={}, values={} }}", identifier_, values_);
}

auto BoundCTERef::ToString() const -> std::string {
  return fmt::format("BoundCTERef {{ alias={}, cte={} }}", alias_, cte_name_);
}

auto BoundSubqueryRef::ToString() const -> std::string {
  std::vector<std::string> columns;
  for (const auto &name : select_list_name_) {
    columns.push_back(fmt::format("{}", fmt::join(name, ".")));
  }
  return fmt::format("BoundSubqueryRef {{\n  alias={},\n  subquery={},\n  columns={},\n}}", alias_,
                     StringUtil::IndentAllLines(subquery_->ToString(), 2, true), columns);
}

}  // namespace bustub
