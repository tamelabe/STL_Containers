#include "../s21_map.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

// Constructors
TEST(Constructor, base) {
  s21::map<int, int> map;
  ASSERT_TRUE(map.size() == 0);
}


// // Modifiers
// TEST(Modifiers, insert) {
//   s21::map<int, int> map;
//   map.insert(std::make_pair(3, 10));
//   map.insert(std::make_pair(2, 20));
//   map.insert(std::make_pair(5, 30));

//   ASSERT_TRUE(map.getRoot()->left->key.first == 2);
//   ASSERT_TRUE(map.getRoot()->left->key.second == 20);
//   ASSERT_TRUE(map.getRoot()->right->key.first == 5);
//   ASSERT_TRUE(map.getRoot()->right->key.second == 30);
// }


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
