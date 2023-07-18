#include "s21_vector.h"

#include <gtest/gtest.h>

#include <cstring>
#include <vector>

// Constructors
TEST(Vector, Constructor_base) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.size() == 0 && vec.capacity() == 0);
  EXPECT_TRUE(vec.data() == nullptr);

  s21::vector<double> vec2;
  EXPECT_TRUE(vec2.size() == 0 && vec2.capacity() == 0);
  EXPECT_TRUE(vec2.data() == nullptr);
}

TEST(Vector, Constructor_size_n) {
  s21::vector<int> vec(2);
  EXPECT_TRUE(vec.capacity() == 2);
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Vector, Constructor_items) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_TRUE(vec.capacity() == 5);
  EXPECT_TRUE(vec.size() == 5);
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec.data()[i]);
  }
}

TEST(Vector, Constructor_copy) {
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

TEST(Vector, Constructor_move) {
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
TEST(Vector, OperatorOverload_move) {
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec2 = std::move(vec);

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE((int)(i + 1) == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == nullptr);
}

TEST(Vector, OperatorOverload_copy) {
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec2 = vec;

  EXPECT_TRUE(vec2.capacity() == 3);
  EXPECT_TRUE(vec2.size() == 3);
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(vec.data()[i] == vec2.data()[i]);
  }
}

// Element access
TEST(Vector, ElementAccess_at) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec.at(2);
  EXPECT_TRUE(a == 3);
}

TEST(Vector, ElementAccess_at_operator) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec[2];
  EXPECT_TRUE(a == 3);
}

TEST(Vector, ElementAccess_front) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec.front();
  EXPECT_TRUE(a == 1);
}

TEST(Vector, ElementAccess_back) {
  s21::vector<int> vec{1, 2, 3};
  int a = vec.back();
  EXPECT_TRUE(a == 3);
}

// Iterators
TEST(Vector, Iterator_begin) {
  s21::vector<int> vec{1, 2, 3};
  int* a = vec.begin();
  EXPECT_TRUE(*a == 1);
}

TEST(Vector, Iterator_end) {
  s21::vector<int> vec{1, 2, 3};
  int* a = vec.end();
  int* b = vec.begin();
  std::advance(b, 3);
  EXPECT_TRUE(a == b);
}

// Capacity
TEST(Vector, Capacity_empty) {
  s21::vector<int> vec;
  s21::vector<int> vec2{1, 2};
  EXPECT_TRUE(vec.empty());
  EXPECT_FALSE(vec2.empty());
}

TEST(Vector, Capacity_size) {
  s21::vector<int> vec{1, 2};
  EXPECT_TRUE(vec.size() == 2);
}

TEST(Vector, Capacity_max_size) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.max_size() == 1073741824U);
}

TEST(Vector, Capacity_capacity) {
  s21::vector<int> vec{1, 2, 3};
  EXPECT_TRUE(vec.capacity() == 3);
}

TEST(Vector, Capacity_reserve) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(5);
  EXPECT_TRUE(vec.size() == 3);
  EXPECT_TRUE(vec.capacity() == 5);
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_TRUE(vec.data()[i] == (int)i + 1);
  }
}

TEST(Vector, Capacity_shrink_to_fit) {
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
TEST(Vector, Modifier_clear) {
  s21::vector<int> vec{1, 2, 3};
  vec.clear();
  EXPECT_TRUE(vec.size() == 0);
  EXPECT_TRUE(vec.capacity() == 3);
}

TEST(Vector, Modifier_insert) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  s21::vector<int>::iterator it = vec.insert(vec.begin() + 1, 777);
  EXPECT_TRUE(vec.size() == 4);
  EXPECT_TRUE(*it == 777);
  EXPECT_TRUE(*(vec.begin() + 1) == 777);
}

TEST(Vector, Modifier_erase) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  vec.erase(vec.begin() + 1);
  EXPECT_TRUE(vec.size() == 2);
  EXPECT_TRUE(vec.data()[0] == 100);
  EXPECT_TRUE(vec.data()[1] == 300);
}

TEST(Vector, Modifier_push_back) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  vec.push_back(777);
  EXPECT_TRUE(vec.size() == 4);
  EXPECT_TRUE(vec.data()[0] == 100);
  EXPECT_TRUE(vec.data()[1] == 200);
  EXPECT_TRUE(vec.data()[2] == 300);
  EXPECT_TRUE(vec.data()[3] == 777);
}

TEST(Vector, Modifier_pop_back) {
  s21::vector<int> vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == 3);
  vec.pop_back();
  EXPECT_TRUE(vec.size() == 2);
  EXPECT_TRUE(vec.data()[0] == 100);
  EXPECT_TRUE(vec.data()[1] == 200);
}

TEST(Vector, Modifier_swap) {
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

// Bonus
TEST(Vector, insert_many) {
  s21::vector<int> vec{100, 200, 300};
  s21::vector<int>::const_iterator it = vec.begin() + 1;
  auto res = vec.insert_many(it, 777, 666, 555);
  EXPECT_TRUE(vec.size() == 6);
  EXPECT_TRUE(*res == 555);
  EXPECT_TRUE(*(vec.begin() + 1) == 777);
}

TEST(Vector, insert_many_back) {
  s21::vector<int> vec{100, 200, 300};
  vec.insert_many_back(777, 666, 555);
  EXPECT_TRUE(vec.size() == 6);
  EXPECT_TRUE(vec.back() == 555);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
