#include "s21_vector.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

// Constructors
TEST(Constructor, base) {
  s21::Vector<int> vec;
  EXPECT_TRUE(vec.size() == 0 && vec.capacity() == 0);
  EXPECT_TRUE(vec.data() == nullptr);

  s21::Vector<double> vec2;
  EXPECT_TRUE(vec2.size() == 0 && vec2.capacity() == 0);
  EXPECT_TRUE(vec2.data() == nullptr);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
