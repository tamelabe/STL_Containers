#include "s21_set.h"

#include <gtest/gtest.h>

#include <cstring>

template <class T>
bool comparisonSet(s21::set<T> &s21_set, s21::set<T> &s21_set2);
template <class T>
bool comparisonSet(s21::set<T> &s21_set, std::set<T> &std_set);

// Constructors
TEST(member_functions, base_constructor_int) {
  s21::set<int> set;
  std::set<int> stdset;
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.size() == 0);
  ASSERT_TRUE(set.begin().getNode() == nullptr);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, base_constructor_char) {
  s21::set<char> set;
  std::set<char> stdset;
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.size() == 0);
  ASSERT_TRUE(set.begin().getNode() == nullptr);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, initializer_list_one_element_char) {
  s21::set<char> set{'a'};
  std::set<char> stdset{'a'};
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.size() == 1);
  ASSERT_TRUE(set.begin().getNode()->key == 'a');
  ASSERT_TRUE(set.end().getNode() == nullptr);
  std::set<int> set2{1};
}

TEST(member_functions, initializer_list_one_element_double) {
  s21::set<double> set{1.0};
  std::set<double> stdset{1.0};
  std::set<double> std_another_set{2.0};
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_FALSE(comparisonSet(set, std_another_set));
  ASSERT_TRUE(set.size() == 1);
  ASSERT_TRUE(set.begin().getNode()->key == 1.0);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, initializer_list_std_pair) {
  s21::set<std::pair<int, int>> set{std::make_pair(1, 2)};
  std::set<std::pair<int, int>> stdset{std::make_pair(1, 2)};
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.size() == 1);
  ASSERT_TRUE(set.begin().getNode()->key.first == 1);
  ASSERT_TRUE(set.begin().getNode()->key.second == 2);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, initializer_list_int) {
  s21::set<int> set{1, 2, 3, 4};
  std::set<int> stdset{1, 2, 3, 4};
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.size() == 4);
  ASSERT_TRUE(set.begin().getNode()->key == 1);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, initializer_list_char) {
  s21::set<char> set{'a', 'b', 'c', 'd'};
  std::set<char> stdset{'a', 'b', 'c', 'd'};
  comparisonSet(set, stdset);
  ASSERT_TRUE(set.size() == 4);
  ASSERT_TRUE(set.begin().getNode()->key == 'a');
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, copy_constructor) {
  s21::set<int> set{1, 2, 3, 4};
  s21::set<int> copySet(set);
  ASSERT_TRUE(comparisonSet(set, copySet));
}

TEST(member_functions, move_constructor) {
  s21::set<int> set{1, 2, 3, 4};
  s21::set<int> copySet(set);
  s21::set<int> moveSet(std::move(set));
  ASSERT_TRUE(!comparisonSet(set, moveSet));
  ASSERT_TRUE(comparisonSet(moveSet, copySet));
}

TEST(member_functions, move_operator) {
  s21::set<int> set{1, 2, 3, 4};
  s21::set<int> copySet(set);
  s21::set<int> moveSet = std::move(set);
  ASSERT_TRUE(!comparisonSet(set, moveSet));
  ASSERT_TRUE(comparisonSet(moveSet, copySet));
}

TEST(Iterators, begin) {
  s21::set<int> set{1, 2, 3, 4};
  std::set<int> stdset{1, 2, 3, 4};
  ASSERT_TRUE(*set.begin() == *stdset.begin());
  ASSERT_TRUE(set.begin().getNode()->key == 1);
}

TEST(Iterators, end) {
  s21::set<int> set{1, 2, 3, 4};
  std::set<int> stdset{1, 2, 3, 4};
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(Capacity, empty) {
  s21::set<int> set;
  std::set<int> stdset;
  ASSERT_TRUE(set.empty() == stdset.empty());
  s21::set<int> set2{5};
  s21::set<int> stdset2{5};
  ASSERT_TRUE(set2.empty() == stdset2.empty());
}

TEST(Capacity, max_size) {
  s21::set<int> set;
  std::set<int> stdset;
  ASSERT_TRUE(set.max_size() > 0);
  ASSERT_TRUE(set.max_size() == 288230376151711742);
}

// Modifiers
TEST(Modifiers, empty) {
  s21::set<int> set{1, 2, 3, 4};
  set.clear();
  std::set<int> stdset{1, 2, 3, 4};
  stdset.clear();
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.size() == 0);
}

TEST(Modifiers, insert_pair) {
  s21::set<std::pair<int, int>> set;
  set.insert(std::make_pair(3, 10));
  ASSERT_TRUE(set.contains(std::make_pair(3, 10)) == true);
}

TEST(Modifiers, insert_key_value) {
  s21::set<char> set;
  set.insert('b');
  set.insert('a');
  std::set<char> stdset;
  stdset.insert('a');
  stdset.insert('b');
  ASSERT_TRUE(comparisonSet(set, stdset));
  ASSERT_TRUE(set.contains('a') == true);
  ASSERT_TRUE(set.contains('b') == true);
}

TEST(Modifiers, insert_key_value_int) {
  s21::set<int> set;
  set.insert(1);
  set.insert(2);
  std::set<int> stdset;
  stdset.insert(1);
  stdset.insert(2);
  ASSERT_TRUE(comparisonSet(set, stdset));
}

TEST(Modifiers, erase_no_child) {
  s21::set<int> set;
  set.insert(7);
  set.insert(3);
  set.erase(set.find(3));
  ASSERT_TRUE(set.size() == 1);
  ASSERT_FALSE(set.contains(3));
}

TEST(Modifiers, erase_one_child) {
  s21::set<int> set;
  set.insert(7);
  set.insert(3);
  set.insert(8);
  set.insert(2);
  set.erase(set.find(3));
  ASSERT_TRUE(set.size() == 3);
  ASSERT_TRUE(set.contains(3) == false);
  ASSERT_TRUE(set.find(7).getNode()->left->key == 2);
}

TEST(Modifiers, erase_two_child) {
  s21::set<int> set;
  set.insert(7);
  set.insert(3);
  set.insert(8);
  set.insert(2);
  set.insert(4);
  set.erase(set.find(3));
  ASSERT_TRUE(set.size() == 4);
  ASSERT_TRUE(set.contains(3) == false);
}

TEST(Modifiers, erase_two_child_2) {
  s21::set<int> set;
  set.insert(8);
  set.insert(4);
  set.insert(11);
  set.insert(2);
  set.insert(6);
  set.insert(9);
  set.insert(12);
  set.insert(1);
  set.insert(3);
  set.insert(5);
  set.insert(7);
  set.insert(10);
  set.erase(set.find(4));
  ASSERT_TRUE(set.size() == 11);
  ASSERT_TRUE(set.contains(4) == false);
}

TEST(Modifiers, merge) {
  s21::set<int> set{8, 4, 11};
  s21::set<int> set1{1, 10, 11};
  set.merge(set1);
  ASSERT_TRUE(set.size() == 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class T>
bool comparisonSet(s21::set<T> &s21_set, std::set<T> &stl_set) {
  if (s21_set.empty() == true || stl_set.empty() == true) {
    return true;
  }
  if (s21_set.size() != stl_set.size()) {
    return false;
  }
  auto it1 = s21_set.begin();
  auto it2 = stl_set.begin();
  for (size_t size = 0; size < s21_set.size(); ++size, ++it1, ++it2) {
    if (*it1 != *it2) {
      return false;
    }
  }
  return true;
}

template <class T>
bool comparisonSet(s21::set<T> &s21_set, s21::set<T> &s21_set2) {
  if (s21_set.size() != s21_set2.size() ||
      s21_set.empty() != s21_set2.empty()) {
    return false;
  }
  auto it1 = s21_set.begin();
  auto it2 = s21_set2.begin();
  for (size_t size = 0; size < s21_set.size(); ++size, ++it1, ++it2) {
    if (*it1 != *it2) return false;
  }
  return true;
}
