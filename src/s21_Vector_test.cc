#include "s21_vector.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstring>

TEST(Constructors, base) {
  s21::Vector<int> vec;
  EXPECT_TRUE(vec.size() == 0);
  EXPECT_TRUE(vec.capacity() == 0);
  EXPECT_TRUE(vec.data() == nullptr);
}

TEST(Constructors, size_n) {
  s21::Vector<int> vec(2);
  EXPECT_TRUE(vec.capacity() == 2);
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Constructors, items) {
  s21::Vector<int> vec{10,8,6,4,2};
  EXPECT_TRUE(vec.capacity() == 5);
  EXPECT_TRUE(vec.size() == 5);
  
  // TODO: add assert for values
}

TEST(Constructors, copy) {
  s21::Vector<int> vec{10,8,6,4,2};
  s21::Vector<int> vec2(vec);
  EXPECT_TRUE(vec2.capacity() == 5);
  EXPECT_TRUE(vec2.size() == 5);
  
  // TODO: add assert for vec2 values
}

TEST(Constructor, move) {
  s21::Vector<int> vec{1,2,3};
  s21::Vector<int> vec2(std::move(vec));
  std::cout << "LOG:" << vec.size() << std::endl;
  std::cout << "LOG:" << vec.capacity() << std::endl;
  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  // EXPECT_TRUE(vec.capacity() == 0);
  // EXPECT_TRUE(vec.size() == 0);
  
  // TODO: add assert for values in vec2
  // TODO: add assert for empty values in vec
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
