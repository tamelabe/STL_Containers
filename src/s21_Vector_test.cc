#include "s21_vector.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstring>

// Constructors
TEST(Constructor, base) {
  s21::Vector<int> vec;
  EXPECT_TRUE(vec.size() == 0 && vec.capacity() == 0);
  EXPECT_TRUE(vec.data() == nullptr);

  s21::Vector<double> vec2;
  EXPECT_TRUE(vec2.size() == 0 && vec2.capacity() == 0);
  EXPECT_TRUE(vec2.data() == nullptr);
}

TEST(Constructor, size_n) {
  s21::Vector<int> vec(2);
  EXPECT_TRUE(vec.capacity() == 2);
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Constructor, items) {
  s21::Vector<int> vec{1,2,3,4,5};
  EXPECT_TRUE(vec.capacity() == 5);
  EXPECT_TRUE(vec.size() == 5);
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec.data()[i]);
  }
}

TEST(Constructor, copy) {
  s21::Vector<int> vec{1,2,3};
  s21::Vector<int> vec2(vec);
  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
}

TEST(Constructor, move) {
  s21::Vector<int> vec{1,2,3};
  s21::Vector<int> vec2(std::move(vec));

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == nullptr);
}

// Overloads
TEST(OperatorOverload, move) {
  s21::Vector<int> vec{1,2,3};
  s21::Vector<int> vec2 = std::move(vec);

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == nullptr);
}

TEST(OperatorOverload, copy) {
  s21::Vector<int> vec{1,2,3};
  s21::Vector<int> vec2 = vec;

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(vec.data()[i] == vec2.data()[i]);
  }
}

// Element access
TEST(ElementAccess, at) {
  s21::Vector<int> vec{1,2,3};
  int a = vec.at(2);
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, at_operator) {
  s21::Vector<int> vec{1,2,3};
  int a = vec[2];
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, front) {
  s21::Vector<int> vec{1,2,3};
  int a = vec.front();
  EXPECT_TRUE(a == 1);
}

TEST(ElementAccess, back) {
  s21::Vector<int> vec{1,2,3};
  int a = vec.back();
  EXPECT_TRUE(a == 3);
}

// Iterators
TEST(Iterator, begin) {
  s21::Vector<int> vec{1,2,3};
  int * a = vec.begin();
  EXPECT_TRUE(*a == 1);
}

TEST(Iterator, end) {
  s21::Vector<int> vec{1,2,3};
  int * a = vec.end();
  int * b = vec.begin();
  std::advance(b, 3);
  EXPECT_TRUE(a == b);
}

// Capacity
TEST(Capacity, empty) {
  s21::Vector<int> vec;
  s21::Vector<int> vec2{1,2};
  EXPECT_TRUE(vec.empty());
  EXPECT_FALSE(vec2.empty());
}

TEST(Capacity, size) {
  s21::Vector<int> vec{1,2};
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Capacity, max_size) {
  s21::Vector<int> vec;
  EXPECT_TRUE(vec.max_size() == 1073741824U);
}

TEST(Capacity, capacity) {
  s21::Vector<int> vec{1,2,3};
  EXPECT_TRUE(vec.capacity() == 3);
}

TEST(Capacity, reserve) {
  s21::Vector<int> vec{1,2,3};
  vec.reserve(5);
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_TRUE(vec.data()[i] == (int)i+1);
  }
  
  EXPECT_TRUE(vec.size() == 3);
  EXPECT_TRUE(vec.capacity() == 5);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
