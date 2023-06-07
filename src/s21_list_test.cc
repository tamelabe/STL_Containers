#include "./s21_list.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <iostream>
#include <list>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Constructor, base) {
  s21::List<int> lst(3);
  EXPECT_TRUE(lst.size() == 3);
}
