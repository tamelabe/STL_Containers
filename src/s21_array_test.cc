#include "s21_array.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <iostream>
#include <vector>

// Constructors
TEST(Constructor, base) {
  s21::Array<int, 3> arr;
  EXPECT_TRUE(arr.size() == 3);
  EXPECT_TRUE(arr.data());
}

TEST(Constructor, items) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_TRUE(arr.size() == 5);
  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_TRUE((int)(i + 1) == arr.data()[i]);
  }
}

TEST(Constructor, items_less) {
  s21::Array<int, 3> arr2{1, 2};
  EXPECT_TRUE(arr2.size() == 3);
  EXPECT_TRUE(arr2.data()[0] == 1);
  EXPECT_TRUE(arr2.data()[1] == 2);
  EXPECT_TRUE(arr2.data()[2] == 0);
}

TEST(Constructor, items_error) {
  EXPECT_THROW((s21::Array<int, 2>{1, 2, 3}), std::length_error);
}

TEST(Constructor, copy) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2(arr);
  EXPECT_TRUE(arr2.size() == 3);
  for (size_t i = 0; i < arr2.size(); i++) {
    EXPECT_TRUE(arr.data()[i] == arr2.data()[i]);
  }
}

TEST(Constructor, move) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2(std::move(arr));

  EXPECT_TRUE(arr2.size() == 3);
  EXPECT_TRUE(arr.size() == 0);
  for (size_t i = 0; i < arr2.size(); i++) {
    EXPECT_TRUE((int)(i + 1) == arr2.data()[i]);
    EXPECT_TRUE(0 == arr.data()[i]);
  }
}

// Overloads
TEST(OperatorOverload, move) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2 = std::move(arr);

  EXPECT_TRUE(arr2.size() == 3);
  for (size_t i = 0; i < arr2.size(); i++) {
    EXPECT_TRUE((int)(i + 1) == arr2.data()[i]);
    EXPECT_TRUE(0 == arr.data()[i]);
  }
}

// Element access
TEST(ElementAccess, at) {
  s21::Array<int, 3> arr{1, 2, 3};
  int a = arr.at(2);
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, at_error) {
  EXPECT_THROW(({
                 s21::Array<int, 3> arr{1, 2, 3};
                 arr.at(4);
               }),
               std::out_of_range);
}

TEST(ElementAccess, at_operator) {
  s21::Array<int, 3> arr{1, 2, 3};
  int a = arr[2];
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, at_operator_error) {
  EXPECT_THROW(({
                 s21::Array<int, 3> arr{1, 2, 3};
                 arr[4];
               }),
               std::out_of_range);
}

TEST(ElementAccess, front) {
  s21::Array<int, 3> arr{1, 2, 3};
  int a = arr.front();
  EXPECT_TRUE(a == 1);
}

TEST(ElementAccess, front_empty) {
  EXPECT_THROW(({
                 s21::Array<int, 0> arr;
                 arr.front();
               }),
               std::out_of_range);
}

TEST(ElementAccess, back) {
  s21::Array<int, 3> arr{1, 2, 3};
  int a = arr.back();
  EXPECT_TRUE(a == 3);
}

TEST(ElementAccess, back_empty) {
  EXPECT_THROW(({
                 s21::Array<int, 0> arr;
                 arr.back();
               }),
               std::out_of_range);
}

// Iterators
TEST(Iterator, begin) {
  s21::Array<int, 3> arr{1, 2, 3};
  int* a = arr.begin();
  EXPECT_TRUE(*a == 1);
}

TEST(Iterator, end) {
  s21::Array<int, 3> arr{1, 2, 3};
  int* a = arr.end();
  EXPECT_TRUE(*(a - 1) == 3);
}

// // Capacity
// TEST(Capacity, empty) {
//   s21::Vector<int> vec;
//   s21::Vector<int> vec2{1, 2};
//   EXPECT_TRUE(vec.empty());
//   EXPECT_FALSE(vec2.empty());
// }

// TEST(Capacity, size) {
//   s21::Vector<int> vec{1, 2};
//   EXPECT_TRUE(vec.size() == 2);
// }

// TEST(Capacity, max_size) {
//   s21::Vector<int> vec;
//   EXPECT_TRUE(vec.max_size() == 1073741824U);
// }

// TEST(Capacity, capacity) {
//   s21::Vector<int> vec{1, 2, 3};
//   EXPECT_TRUE(vec.capacity() == 3);
// }

// // LEAK
// TEST(Capacity, reserve) {
//   s21::Vector<int> vec{1, 2, 3};
//   vec.reserve(5);
//   EXPECT_TRUE(vec.size() == 3);
//   EXPECT_TRUE(vec.capacity() == 5);
//   for (size_t i = 0; i < vec.size(); i++) {
//     EXPECT_TRUE(vec.data()[i] == (int)i + 1);
//   }
// }

// // LEAK
// TEST(Capacity, shrink_to_fit) {
//   s21::Vector<int> vec{1, 2, 3};
//   vec.reserve(5);
//   EXPECT_TRUE(vec.size() == 3);
//   EXPECT_TRUE(vec.capacity() == 5);
//   vec.shrink_to_fit();
//   EXPECT_TRUE(vec.capacity() == 3);
//   for (size_t i = 0; i < vec.size(); i++) {
//     EXPECT_TRUE(vec.data()[i] == (int)i + 1);
//   }
// }

// // Modifier
// TEST(Modifier, clear) {
//   s21::Vector<int> vec{1, 2, 3};
//   vec.clear();
//   EXPECT_TRUE(vec.size() == 0);
//   EXPECT_TRUE(vec.capacity() == 3);
// }

// TEST(Modifier, insert) {
//   s21::Vector<int> vec{100, 200, 300};
//   EXPECT_TRUE(vec.size() == 3);
//   s21::Vector<int>::iterator it = vec.insert(vec.begin() + 1, 777);
//   EXPECT_TRUE(vec.size() == 4);
//   EXPECT_TRUE(*it == 777);
//   EXPECT_TRUE(*(vec.begin() + 1) == 777);
// }

// TEST(Modifier, erase) {
//   s21::Vector<int> vec{100, 200, 300};
//   EXPECT_TRUE(vec.size() == 3);
//   vec.erase(vec.begin() + 1);
//   EXPECT_TRUE(vec.size() == 2);
//   EXPECT_TRUE(vec.data()[0] == 100);
//   EXPECT_TRUE(vec.data()[1] == 300);
// }

// TEST(Modifier, push_back) {
//   s21::Vector<int> vec{100, 200, 300};
//   EXPECT_TRUE(vec.size() == 3);
//   vec.push_back(777);
//   EXPECT_TRUE(vec.size() == 4);
//   EXPECT_TRUE(vec.data()[0] == 100);
//   EXPECT_TRUE(vec.data()[1] == 200);
//   EXPECT_TRUE(vec.data()[2] == 300);
//   EXPECT_TRUE(vec.data()[3] == 777);
// }

// TEST(Modifier, pop_back) {
//   s21::Vector<int> vec{100, 200, 300};
//   EXPECT_TRUE(vec.size() == 3);
//   vec.pop_back();
//   EXPECT_TRUE(vec.size() == 2);
//   EXPECT_TRUE(vec.data()[0] == 100);
//   EXPECT_TRUE(vec.data()[1] == 200);
// }

// TEST(Modifier, pop_back2) {
//   s21::Vector<int> vec{100, 200, 300};
//   EXPECT_TRUE(vec.size() == 3);
//   vec.pop_back();
//   vec.pop_back();
//   vec.pop_back();
//   vec.pop_back();
//   EXPECT_TRUE(vec.size() == 0);
// }

// TEST(Modifier, swap) {
//   s21::Vector<int> vec{100, 200, 300};
//   s21::Vector<int> vec2{1000, 2000, 3000};
//   vec.swap(vec2);
//   EXPECT_TRUE(vec.data()[0] == 1000);
//   EXPECT_TRUE(vec.data()[1] == 2000);
//   EXPECT_TRUE(vec.data()[2] == 3000);
//   EXPECT_TRUE(vec2.data()[0] == 100);
//   EXPECT_TRUE(vec2.data()[1] == 200);
//   EXPECT_TRUE(vec2.data()[2] == 300);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
