#include "../s21_map.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

// Constructors
TEST(member_functions, base_constructor) {
  s21::map<int, int> map;
  ASSERT_TRUE(map.size() == 0);
}

TEST(member_functions, initializer_list) {
  s21::map<int, char> map{
    std::pair<int, char> {4, 'a'},
    std::pair<int, char> {2, 'b'},
    std::pair<int, char> {3, 'c'},
    std::pair<int, char> {7, 'd'}
  };
  ASSERT_TRUE(map.size() == 4);
  ASSERT_TRUE(map.at(4) == 'a');
  ASSERT_TRUE(map.at(7) == 'd');
}

TEST(member_functions, copy_constructor) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'},
    std::pair<int, char> {4, 'e'},
    std::pair<int, char> {6, 'f'},
    std::pair<int, char> {8, 'g'}
  };
  s21::map<int, char> map2(map);
  ASSERT_TRUE(map2.size() == 7);
  ASSERT_TRUE(map2.at(5) == 'a');
  ASSERT_TRUE(map2.at(8) == 'g');
  ASSERT_TRUE(map2.at(2) == 'd');
}

TEST(member_functions, move_constructor) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'},
    std::pair<int, char> {4, 'e'}
  };
  s21::map<int, char> map2(std::move(map));
  ASSERT_TRUE(map2.size() == 5);
  ASSERT_TRUE(map2.at(5) == 'a');
  ASSERT_TRUE(map2.at(7) == 'c');
  ASSERT_TRUE(map2.at(2) == 'd');
}

TEST(member_functions, move_operator) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'},
    std::pair<int, char> {4, 'e'}
  };
  s21::map<int, char> map2 = std::move(map);
  ASSERT_TRUE(map2.size() == 5);
  ASSERT_TRUE(map2.at(5) == 'a');
  ASSERT_TRUE(map2.at(7) == 'c');
  ASSERT_TRUE(map2.at(2) == 'd');
}

TEST(element_access, accessor_inserter_element_operator) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'},
    std::pair<int, char> {4, 'e'}
  };
  ASSERT_TRUE(map.size() == 5);
  ASSERT_TRUE(map[5] == 'a');
  ASSERT_TRUE(map[7] == 'c');
  ASSERT_TRUE(map[2] == 'd');
  map[2] = 'g';
  ASSERT_TRUE(map[2] == 'g');
}

TEST(Iterators, begin) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'}
  };
  ASSERT_TRUE(map.begin().getNode()->key == 2);
}

TEST(Iterators, end) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'}
  };
  ASSERT_TRUE(map.end().getNode() == nullptr);
}

TEST(Capacity, empty) {
  s21::map<int, char> map;
  ASSERT_TRUE(map.empty() == true);
  s21::map<int, char> map2{std::pair<int, char> {5, 'a'}};
  ASSERT_TRUE(map2.empty() == false);
}

TEST(Capacity, max_size) {
  s21::map<int, char> map;
  ASSERT_TRUE(map.max_size() == TREE_MAX_SIZE);  // TODO: fix hardcode!
}

// Modifiers
TEST(Modifiers, empty) {
  s21::map<int, char> map{
    std::pair<int, char> {5, 'a'},
    std::pair<int, char> {3, 'b'},
    std::pair<int, char> {7, 'c'},
    std::pair<int, char> {2, 'd'}
  };
  map.clear();
  ASSERT_TRUE(map.size() == 0);
}

TEST(Modifiers, insert_pair_max_size) {
  s21::map<int, int> map;
  map.insert(std::make_pair(3, 10));
  map.insert(std::make_pair(4, 40));
  map.insert(std::make_pair(5, 50));
  map.insert(std::make_pair(6, 60));
  map.insert(std::make_pair(7, 70));
  ASSERT_TRUE(map.at(7) == 70);
  std::pair<s21::BinaryTree<int, int>::iterator, bool> result = map.insert(std::make_pair(8, 80));
  ASSERT_TRUE(result.second == false);
}

TEST(Modifiers, insert_pair) {
  s21::map<int, int> map;
  map.insert(std::make_pair(3, 10));
  ASSERT_TRUE(map.at(3) == 10);
}

TEST(Modifiers, insert_key_value) {
  s21::map<int, char> map;
  map.insert(3, 'a');
  map.insert(2, 'b');
  ASSERT_TRUE(map.at(3) == 'a');
  ASSERT_TRUE(map.at(2) == 'b');
}

TEST(Modifiers, insert_or_assign_key_value) {
  s21::map<int, char> map;
  map.insert(3, 'a');
  ASSERT_TRUE(map.at(3) == 'a');
  map.insert_or_assign(2, 'c');
  ASSERT_TRUE(map.at(2) == 'c');
  map.insert_or_assign(2, 'G');
  ASSERT_TRUE(map.at(2) == 'G');
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
