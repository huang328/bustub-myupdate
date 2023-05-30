add_library(
  bustub_recovery
  OBJECT
  checkpoint_manager.cpp
<<<<<<< HEAD
  log_manager.cpp
  log_recovery.cpp)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_recovery>
    PARENT_SCOPE)
=======
  log_manager.cpp)

set(ALL_OBJECT_FILES
  ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_recovery>
  PARENT_SCOPE)
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
