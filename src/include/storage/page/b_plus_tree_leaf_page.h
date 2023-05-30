//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/include/page/b_plus_tree_leaf_page.h
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#pragma once

<<<<<<< HEAD
=======
#include <string>
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#include <utility>
#include <vector>

#include "storage/page/b_plus_tree_page.h"

namespace bustub {

#define B_PLUS_TREE_LEAF_PAGE_TYPE BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>
<<<<<<< HEAD
#define LEAF_PAGE_HEADER_SIZE 28
=======
#define LEAF_PAGE_HEADER_SIZE 16
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
#define LEAF_PAGE_SIZE ((BUSTUB_PAGE_SIZE - LEAF_PAGE_HEADER_SIZE) / sizeof(MappingType))

/**
 * Store indexed key and record id(record id = page id combined with slot id,
 * see include/common/rid.h for detailed implementation) together within leaf
 * page. Only support unique key.
 *
 * Leaf page format (keys are stored in order):
 *  ----------------------------------------------------------------------
 * | HEADER | KEY(1) + RID(1) | KEY(2) + RID(2) | ... | KEY(n) + RID(n)
 *  ----------------------------------------------------------------------
 *
<<<<<<< HEAD
 *  Header format (size in byte, 28 bytes in total):
 *  ---------------------------------------------------------------------
 * | PageType (4) | LSN (4) | CurrentSize (4) | MaxSize (4) |
 *  ---------------------------------------------------------------------
 *  -----------------------------------------------
 * | ParentPageId (4) | PageId (4) | NextPageId (4)
=======
 *  Header format (size in byte, 16 bytes in total):
 *  ---------------------------------------------------------------------
 * | PageType (4) | CurrentSize (4) | MaxSize (4) |
 *  ---------------------------------------------------------------------
 *  -----------------------------------------------
 * |  NextPageId (4)
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
 *  -----------------------------------------------
 */
INDEX_TEMPLATE_ARGUMENTS
class BPlusTreeLeafPage : public BPlusTreePage {
 public:
<<<<<<< HEAD
  // After creating a new leaf page from buffer pool, must call initialize
  // method to set default values
  void Init(page_id_t page_id, page_id_t parent_id = INVALID_PAGE_ID, int max_size = LEAF_PAGE_SIZE);
=======
  // Delete all constructor / destructor to ensure memory safety
  BPlusTreeLeafPage() = delete;
  BPlusTreeLeafPage(const BPlusTreeLeafPage &other) = delete;

  /**
   * After creating a new leaf page from buffer pool, must call initialize
   * method to set default values
   * @param max_size Max size of the leaf node
   */
  void Init(int max_size = LEAF_PAGE_SIZE);

>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
  // helper methods
  auto GetNextPageId() const -> page_id_t;
  void SetNextPageId(page_id_t next_page_id);
  auto KeyAt(int index) const -> KeyType;
<<<<<<< HEAD
  auto ValueAt(int index) const -> ValueType;
  auto GetItem(int index) const -> const MappingType &;
  auto KeyIndex(const KeyType &key, const KeyComparator &comparator) const -> int;
  auto Lookup(const KeyType &key, ValueType *value, const KeyComparator &comparator) const -> bool;
  auto Insert(const KeyType &key, const ValueType &value, const KeyComparator &comparator) -> int;
  auto MoveHalfTo(BPlusTreeLeafPage *dst_page) -> void;
  auto MoveAllTo(BPlusTreeLeafPage *dst_page) -> void;
  auto CopyData(MappingType *items, int size) -> void;
  auto Remove(const KeyType &key, const KeyComparator &comparator) -> bool;
=======

  /**
   * @brief for test only return a string representing all keys in
   * this leaf page formatted as "(key1,key2,key3,...)"
   *
   * @return std::string
   */
  auto ToString() const -> std::string {
    std::string kstr = "(";
    bool first = true;

    for (int i = 0; i < GetSize(); i++) {
      KeyType key = KeyAt(i);
      if (first) {
        first = false;
      } else {
        kstr.append(",");
      }

      kstr.append(std::to_string(key.ToString()));
    }
    kstr.append(")");

    return kstr;
  }
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

 private:
  page_id_t next_page_id_;
  // Flexible array member for page data.
<<<<<<< HEAD
  MappingType array_[1];
};
}  // namespace bustub
=======
  MappingType array_[0];
};
}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
