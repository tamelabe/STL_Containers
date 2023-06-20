#include "s21_vector.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

// Constructors
TEST(Constructor, base) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.size() == 0 && vec.capacity() == 0);
  EXPECT_TRUE(vec.data() == nullptr);

  s21::vector<double> vec2;
  EXPECT_TRUE(vec2.size() == 0 && vec2.capacity() == 0);
  EXPECT_TRUE(vec2.data() == nullptr);
}

TEST(Constructor, size_n) {
  s21::vector<int> vec(2);
  EXPECT_TRUE(vec.capacity() == 2);
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Constructor, items) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_TRUE(vec.capacity() == 5);
  EXPECT_TRUE(vec.size() == 5);
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec.data()[i]);
  }
}

TEST(Constructor, copy) {
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec2(vec);
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
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec2(std::move(vec));

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == nullptr);
}

// Overloads
TEST(OperatorOverload, move) {
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec2 = std::move(vec);

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == nullptr);
}

TEST(OperatorOverload, copy) {
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec2 = vec;

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(vec.data()[i] == vec2.data()[i]);
  }
}

// Element access
TEST(ElementAccess, at) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec.at(2);
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, at_operator) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec[2];
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, front) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec.front();
  EXPECT_TRUE(a == 1);
}

TEST(ElementAccess, back) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec.back();
  EXPECT_TRUE(a == 3);
}

// Iterators
TEST(Iterator, begin) {
  s21::vector<int> vec{1, 2, 3};
  int* a = vec.begin();
  EXPECT_TRUE(*a == 1);
}

TEST(Iterator, end) {
  s21::vector<int> vec{1, 2, 3};
  int* a = vec.end();
  int* b = vec.begin();
  std::advance(b, 3);
  EXPECT_TRUE(a == b);
}

// Capacity
TEST(Capacity, empty) {
  s21::vector<int> vec;
  s21::vector<int> vec2{1, 2};
  EXPECT_TRUE(vec.empty());
  EXPECT_FALSE(vec2.empty());
}

TEST(Capacity, size) {
  s21::vector<int> vec{1, 2};
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Capacity, max_size) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.max_size() == 1073741824U);
}

TEST(Capacity, capacity) {
  s21::vector<int> vec{1, 2, 3};
  EXPECT_TRUE(vec.capacity() == 3);
}

// LEAK
TEST(Capacity, reserve) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(5);
  EXPECT_TRUE(vec.size() == 3);
  EXPECT_TRUE(vec.capacity() == 5);
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_TRUE(vec.data()[i] == (int)i + 1);
  }
}

// LEAK
TEST(Capacity, shrink_to_fit) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(5);
  EXPECT_TRUE(vec.size() == 3);
  EXPECT_TRUE(vec.capacity() == 5);
  vec.shrink_to_fit();
  EXPECT_TRUE(vec.capacity() == 3);
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_TRUE(vec.data()[i] == (int)i + 1);
  }
}

// Modifier
TEST(Modifier, clear) {
  s21::vector<int> vec{1, 2, 3};
  vec.clear();
  EXPECT_TRUE(vec.size() == 0);
  EXPECT_TRUE(vec.capacity() == 3);
}

TEST(Modifier, insert) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  s21::vector<int>::iterator it = vec.insert(vec.begin() + 1, 777);
  EXPECT_TRUE(vec.size() == 4);
  EXPECT_TRUE(*it == 777);
  EXPECT_TRUE(*(vec.begin() + 1) == 777);
}

TEST(Modifier, erase) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  vec.erase(vec.begin() + 1);
  EXPECT_TRUE(vec.size() == 2);
  EXPECT_TRUE(vec.data()[0] == 100);
  EXPECT_TRUE(vec.data()[1] == 300);
}

TEST(Modifier, push_back) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  vec.push_back(777);
  EXPECT_TRUE(vec.size() == 4);
  EXPECT_TRUE(vec.data()[0] == 100);
  EXPECT_TRUE(vec.data()[1] == 200);
  EXPECT_TRUE(vec.data()[2] == 300);
  EXPECT_TRUE(vec.data()[3] == 777);
}

TEST(Modifier, pop_back) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  vec.pop_back();
  EXPECT_TRUE(vec.size() == 2);
  EXPECT_TRUE(vec.data()[0] == 100);
  EXPECT_TRUE(vec.data()[1] == 200);
}

TEST(Modifier, swap) {
  s21::vector<int> vec{100, 200, 300};
  s21::vector<int> vec2{1000, 2000, 3000};
  vec.swap(vec2);
  EXPECT_TRUE(vec.data()[0] == 1000);
  EXPECT_TRUE(vec.data()[1] == 2000);
  EXPECT_TRUE(vec.data()[2] == 3000);
  EXPECT_TRUE(vec2.data()[0] == 100);
  EXPECT_TRUE(vec2.data()[1] == 200);
  EXPECT_TRUE(vec2.data()[2] == 300);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}