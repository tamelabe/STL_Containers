#include "s21_set.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>


template<class T>
bool comparisonSet(s21::set<T> &s21_set, s21::set<T> &s21_set2);
template<class T>
bool comparisonSet(s21::set<T> &s21_set, std::set<T> &std_set);

// Constructors
TEST(member_functions, base_constructor) {
  s21::set<int> set;
  ASSERT_TRUE(set.size() == 0);
  ASSERT_TRUE(set.begin().getNode() == nullptr);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, initializer_list_one_element) {
  s21::set<int> set { 1 };
  ASSERT_TRUE(set.size() == 1);
  ASSERT_TRUE(set.begin().getNode()->key == 1);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, initializer_list) {
  s21::set<int> set { 1, 2, 3, 4 };
  ASSERT_TRUE(set.size() == 4);
  ASSERT_TRUE(set.begin().getNode()->key == 1);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, copy_constructor) {
  s21::set<int> set { 1, 2, 3, 4 };
  s21::set<int> copySet(set);
  ASSERT_TRUE(comparisonSet(set, copySet));
}

TEST(member_functions, move_constructor) {
  s21::set<int> set { 1, 2, 3, 4 };
  s21::set<int> copySet(set);
  s21::set<int> moveSet(std::move(set));
  ASSERT_TRUE(!comparisonSet(set, moveSet));
  ASSERT_TRUE(comparisonSet(moveSet, copySet));
}

TEST(member_functions, move_operator) {
  s21::set<int> set { 1, 2, 3, 4 };
  s21::set<int> copySet(set);
  s21::set<int> moveSet = std::move(set);
  ASSERT_TRUE(!comparisonSet(set, moveSet));
  ASSERT_TRUE(comparisonSet(moveSet, copySet));
}

TEST(Iterators, begin) {
  s21::set<int> set { 1, 2, 3, 4 };
  ASSERT_TRUE(set.begin().getNode()->key == 1);
}

TEST(Iterators, end) {
  s21::set<int> set { 1, 2, 3, 4 };
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(Capacity, empty) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty() == true);
  s21::set<int> set2 { 5 };
  ASSERT_TRUE(set2.empty() == false);
}

TEST(Capacity, max_size) {
  s21::set<int> set;
  ASSERT_TRUE(set.max_size() == TREE_MAX_SIZE);  // TODO: fix hardcode!
}

// Modifiers
TEST(Modifiers, empty) {
  s21::set<int> set { 1, 2, 3, 4 };
  set.clear();
  ASSERT_TRUE(set.size() == 0);
}

TEST(Modifiers, insert_pair) {
  s21::set<std::pair<int, int>> set;
  set.insert(std::make_pair(3, 10));
  ASSERT_TRUE(set.contains(std::make_pair(3, 10)) == true);
}

TEST(Modifiers, insert_key_value) {
  s21::set<char> set;
  set.insert('a');
  set.insert('b');
  ASSERT_TRUE(set.contains('a') == true);
  ASSERT_TRUE(set.contains('b') == true);
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
  s21::set<int> set{
    {8},
    {4},
    {11}
  };
  s21::set<int> set1{
    {1},
    {10},
    {11}
  };
  set.merge(set1);
  ASSERT_TRUE(set.size() == 5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template<class T>
bool comparisonSet(s21::set<T> &s21_set, std::set<T> &stl_set) {
  if (s21_set.size() != stl_set.size() || 
      s21_set.empty() != stl_set.empty()) {
    return false;
  }
  auto it1 = s21_set.begin();
  auto it2 = stl_set.begin();
  for (size_t size = 0; size < s21_set.size(); ++size, ++it1, ++it2) {
    if (*it1 != *it2) return false;
  }
  return true;
}

template<class T>
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
