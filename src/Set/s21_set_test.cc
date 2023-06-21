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
  s21::set<int> set {
    1,
    2,
    3,
    4
  };
  ASSERT_TRUE(set.size() == 4);
  ASSERT_TRUE(set.begin().getNode()->key == 1);
  ASSERT_TRUE(set.end().getNode() == nullptr);
}

TEST(member_functions, copy_constructor) {
  s21::set<int> set {
    1,
    2,
    3,
    4
  };
  s21::set<int> copySet(set);
  ASSERT_TRUE(comparisonSet(set, copySet));
}

TEST(member_functions, move_constructor) {
  s21::set<int> set {
    1,
    2,
    3,
    4
  };
  s21::set<int> copySet(set);
  s21::set<int> moveSet(std::move(set));
  ASSERT_TRUE(!comparisonSet(set, moveSet));
  ASSERT_TRUE(comparisonSet(moveSet, copySet));
}

TEST(member_functions, move_operator) {
  s21::set<int> set {
    1,
    2,
    3,
    4
  };
  s21::set<int> copySet(set);
  s21::set<int> moveSet = std::move(set);
  ASSERT_TRUE(!comparisonSet(set, moveSet));
  ASSERT_TRUE(comparisonSet(moveSet, copySet));
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