#include "s21_vector.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

TEST(Constructors, base) {
  s21::Vector<int> vec;
  EXPECT_TRUE(vec.size() == 0);
  EXPECT_TRUE(vec.capacity() == 0);
  EXPECT_TRUE(vec.data() == nullptr);
}

TEST(Constructors, with_parameter) {
    s21::Vector<int> vec(2);
    std::vector<int> vec2(2);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
