#include "s21_array.h"

#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <iostream>

// Constructors
TEST(Constructor, base) {
  s21::array<int, 3> s21_arr;
  std::array<int, 3> std_arr;
  EXPECT_TRUE(s21_arr.size() == std_arr.size());
}

TEST(Constructor, base_2) {
  std::array<int, 0> std_arr;
  s21::array<int, 0> s21_arr;
  EXPECT_TRUE(std_arr.size() == 0);
  EXPECT_TRUE(s21_arr.size() == 0);
}

// TEST(Constructor, items) {
//   s21::array<int, 5> arr{1, 2, 3, 4, 5};
//   EXPECT_TRUE(arr.size() == 5);
//   for (size_t i = 0; i < arr.size(); i++) {
//     EXPECT_TRUE((int)(i + 1) == arr.data()[i]);
//   }
// }

// TEST(Constructor, items_less) {
//   s21::array<int, 3> arr2{1, 2};
//   EXPECT_TRUE(arr2.size() == 3);
//   EXPECT_TRUE(arr2.data()[0] == 1);
//   EXPECT_TRUE(arr2.data()[1] == 2);
//   EXPECT_TRUE(arr2.data()[2] == 0);
// }

// TEST(Constructor, items_error) {
//   EXPECT_THROW((s21::array<int, 2>{1, 2, 3}), std::length_error);
// }

// TEST(Constructor, copy) {
//   s21::array<int, 3> arr{1, 2, 3};
//   s21::array<int, 3> arr2(arr);
//   EXPECT_TRUE(arr2.size() == 3);
//   for (size_t i = 0; i < arr2.size(); i++) {
//     EXPECT_TRUE(arr.data()[i] == arr2.data()[i]);
//   }
// }

// TEST(Constructor, move) {
//   s21::array<int, 3> arr{1, 2, 3};
//   s21::array<int, 3> arr2(std::move(arr));

//   EXPECT_TRUE(arr2.size() == 3);
//   EXPECT_TRUE(arr.size() == 0);
//   for (size_t i = 0; i < arr2.size(); i++) {
//     EXPECT_TRUE((int)(i + 1) == arr2.data()[i]);
//     EXPECT_TRUE(0 == arr.data()[i]);
//   }
// }

// // Overloads
// TEST(OperatorOverload, move) {
//   s21::array<int, 3> arr{1, 2, 3};
//   s21::array<int, 3> arr2 = std::move(arr);

//   EXPECT_TRUE(arr2.size() == 3);
//   for (size_t i = 0; i < arr2.size(); i++) {
//     EXPECT_TRUE((int)(i + 1) == arr2.data()[i]);
//     EXPECT_TRUE(0 == arr.data()[i]);
//   }
// }

// // Element access
// TEST(ElementAccess, at) {
//   s21::array<int, 3> arr{1, 2, 3};
//   int a = arr.at(2);
//   EXPECT_TRUE(a == 3);
// }

// TEST(ElementAccess, at_error) {
//   s21::array<int, 3> arr{1, 2, 3};
//   EXPECT_THROW(arr.at(4), std::out_of_range);
// }

// TEST(ElementAccess, at_operator) {
//   s21::array<int, 3> arr{1, 2, 3};
//   int a = arr[2];
//   EXPECT_TRUE(a == 3);
// }

// TEST(ElementAccess, at_operator_error) {
//   s21::array<int, 3> arr{1, 2, 3};
//   EXPECT_THROW(arr[4], std::out_of_range);
// }

// TEST(ElementAccess, front) {
//   s21::array<int, 3> arr{1, 2, 3};
//   int a = arr.front();
//   EXPECT_TRUE(a == 1);
// }

// TEST(ElementAccess, front_empty) {
//   s21::array<int, 0> arr;
//   EXPECT_THROW(arr.front(), std::out_of_range);
// }

// TEST(ElementAccess, back) {
//   s21::array<int, 3> arr{1, 2, 3};
//   int a = arr.back();
//   EXPECT_TRUE(a == 3);
// }

// TEST(ElementAccess, back_empty) {
//   s21::array<int, 0> arr;
//   EXPECT_THROW(arr.back(), std::out_of_range);
// }

// // Iterators
// TEST(Iterator, begin) {
//   s21::array<int, 3> arr{1, 2, 3};
//   int* a = arr.begin();
//   EXPECT_TRUE(*a == 1);
// }

// TEST(Iterator, end) {
//   s21::array<int, 3> arr{1, 2, 3};
//   int* a = arr.end();
//   EXPECT_TRUE(*(a - 1) == 3);
// }

// // Capacity
// TEST(Capacity, empty) {
//   s21::array<int, 0> arr;
//   s21::array<int, 2> arr2{1, 2};
//   EXPECT_TRUE(arr.empty());
//   EXPECT_FALSE(arr2.empty());
// }

// TEST(Capacity, size) {
//   s21::array<int, 2> arr{1, 2};
//   EXPECT_TRUE(arr.size() == 2);
// }

// TEST(Capacity, max_size) {
//   s21::array<int, 10> arr;
//   EXPECT_TRUE(arr.max_size() == 10);
// }

// TEST(Modifier, swap) {
//   s21::array<int, 3> arr{100, 200, 300};
//   s21::array<int, 3> arr2{1000, 2000, 3000};
//   arr.swap(arr2);
//   EXPECT_TRUE(arr.data()[0] == 1000);
//   EXPECT_TRUE(arr.data()[1] == 2000);
//   EXPECT_TRUE(arr.data()[2] == 3000);
//   EXPECT_TRUE(arr2.data()[0] == 100);
//   EXPECT_TRUE(arr2.data()[1] == 200);
//   EXPECT_TRUE(arr2.data()[2] == 300);
// }

// TEST(Modifier, fill) {
//   s21::array<int, 3> arr;
//   arr.fill(7);
//   EXPECT_TRUE(arr.data()[0] == 7);
//   EXPECT_TRUE(arr.data()[1] == 7);
//   EXPECT_TRUE(arr.data()[2] == 7);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
