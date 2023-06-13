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
}

TEST(member_functions, initializer_list) {
  s21::set<int> set {
    1,
    2,
    3,
    4
  };
  ASSERT_TRUE(set.size() == 4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
