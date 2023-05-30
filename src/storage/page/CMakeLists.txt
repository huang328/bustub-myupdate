add_library(
    bustub_storage_page
    OBJECT
    b_plus_tree_internal_page.cpp
    b_plus_tree_leaf_page.cpp
    b_plus_tree_page.cpp
    hash_table_block_page.cpp
    hash_table_bucket_page.cpp
    hash_table_directory_page.cpp
<<<<<<< HEAD
    header_page.cpp
=======
    page_guard.cpp
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
    table_page.cpp)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_storage_page>
    PARENT_SCOPE)
