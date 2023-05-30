//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/page/b_plus_tree_page.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "storage/page/b_plus_tree_page.h"

namespace bustub {

/*
 * Helper methods to get/set page type
 * Page type enum class is defined in b_plus_tree_page.h
 */
<<<<<<< HEAD
auto BPlusTreePage::IsLeafPage() const -> bool { return page_type_ == IndexPageType::LEAF_PAGE; }
auto BPlusTreePage::IsRootPage() const -> bool { return parent_page_id_ == INVALID_PAGE_ID; }
void BPlusTreePage::SetPageType(IndexPageType page_type) { page_type_ = page_type; }
=======
auto BPlusTreePage::IsLeafPage() const -> bool { return false; }
void BPlusTreePage::SetPageType(IndexPageType page_type) {}
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

/*
 * Helper methods to get/set size (number of key/value pairs stored in that
 * page)
 */
<<<<<<< HEAD
auto BPlusTreePage::GetSize() const -> int { return size_; }
void BPlusTreePage::SetSize(int size) { size_ = size; }
void BPlusTreePage::IncreaseSize(int amount) { size_ += amount; }
=======
auto BPlusTreePage::GetSize() const -> int { return 0; }
void BPlusTreePage::SetSize(int size) {}
void BPlusTreePage::IncreaseSize(int amount) {}
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

/*
 * Helper methods to get/set max size (capacity) of the page
 */
<<<<<<< HEAD
auto BPlusTreePage::GetMaxSize() const -> int { return max_size_; }
void BPlusTreePage::SetMaxSize(int size) { max_size_ = size; }
=======
auto BPlusTreePage::GetMaxSize() const -> int { return 0; }
void BPlusTreePage::SetMaxSize(int size) {}
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850

/*
 * Helper method to get min page size
 * Generally, min page size == max page size / 2
 */
<<<<<<< HEAD
auto BPlusTreePage::GetMinSize() const -> int {
  if (IsLeafPage()) {
    return max_size_ / 2;
  }
  return (max_size_ + 1) / 2;
}

/*
 * Helper methods to get/set parent page id
 */
auto BPlusTreePage::GetParentPageId() const -> page_id_t { return parent_page_id_; }
void BPlusTreePage::SetParentPageId(page_id_t parent_page_id) { parent_page_id_ = parent_page_id; }

/*
 * Helper methods to get/set self page id
 */
auto BPlusTreePage::GetPageId() const -> page_id_t { return page_id_; }
void BPlusTreePage::SetPageId(page_id_t page_id) { page_id_ = page_id; }

/*
 * Helper methods to set lsn
 */
void BPlusTreePage::SetLSN(lsn_t lsn) { lsn_ = lsn; }

}  // namespace bustub
=======
auto BPlusTreePage::GetMinSize() const -> int { return 0; }

}  // namespace bustub
>>>>>>> dfa6cd4e82ef42eb111b889604cbf280771b7850
