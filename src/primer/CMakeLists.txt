add_library(
  bustub_primer
  OBJECT
<<<<<<< HEAD
  p0_trie.cpp)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_primer>
    PARENT_SCOPE)
=======
  trie.cpp
  trie_store.cpp)

set(ALL_OBJECT_FILES
  ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:bustub_primer>
  PARENT_SCOPE)
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
