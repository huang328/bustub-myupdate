add_library(
  bustub_common
  OBJECT
  bustub_instance.cpp
<<<<<<< HEAD
=======
  bustub_ddl.cpp
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
  config.cpp
  util/string_util.cpp)

set(ALL_OBJECT_FILES
<<<<<<< HEAD
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_common>
    PARENT_SCOPE)
=======
  ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_common>
  PARENT_SCOPE)
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
