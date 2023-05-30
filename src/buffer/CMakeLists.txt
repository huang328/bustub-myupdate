add_library(
        bustub_buffer
        OBJECT
<<<<<<< HEAD
        buffer_pool_manager_instance.cpp
=======
        buffer_pool_manager.cpp
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
        clock_replacer.cpp
        lru_replacer.cpp
        lru_k_replacer.cpp)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_buffer>
        PARENT_SCOPE)
