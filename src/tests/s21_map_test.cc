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

TEST(Constructor, initializer_list) {
  s21::map<int, int> map{
    std::pair<int, int> {4.0, 'a'},
    std::pair<int, int> {2.0, 'b'},
    std::pair<int, int> {3.0, 'c'},
    std::pair<int, int> {7.0, 'd'}
  };
  std::cout << map.size() << std::endl;
  ASSERT_TRUE(map.size() == 4);
  ASSERT_TRUE(map.getRoot()->left->key.first == 2);
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
