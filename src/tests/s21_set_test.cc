#include "../s21_set.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

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
  ASSERT_TRUE(copySet.size() == set.size());
  ASSERT_TRUE(copySet.begin() == set.size());

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template<class T>
bool comparisonSet(s21::set<T> &s21_set, std::set<T> &stl_set) {
  if (s21_set.size() != stl_set.size()) {}
}
