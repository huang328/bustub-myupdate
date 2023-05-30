add_library(
<<<<<<< HEAD
    bustub_optimizer
    OBJECT
    eliminate_true_filter.cpp
    merge_projection.cpp
    merge_filter_nlj.cpp
    merge_filter_scan.cpp
    nlj_as_hash_join.cpp
    nlj_as_index_join.cpp
    optimizer.cpp
    optimizer_custom_rules.cpp
    order_by_index_scan.cpp
    sort_limit_as_topn.cpp)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_optimizer>
    PARENT_SCOPE)
=======
        bustub_optimizer
        OBJECT
        eliminate_true_filter.cpp
        merge_projection.cpp
        merge_filter_nlj.cpp
        merge_filter_scan.cpp
        nlj_as_hash_join.cpp
        nlj_as_index_join.cpp
        optimizer.cpp
        optimizer_custom_rules.cpp
        optimizer_internal.cpp
        order_by_index_scan.cpp
        sort_limit_as_topn.cpp)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_optimizer>
        PARENT_SCOPE)
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
