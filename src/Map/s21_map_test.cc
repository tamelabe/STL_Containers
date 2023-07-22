#include "s21_map.h"

#include <gtest/gtest.h>

#include <cstring>
#include <map>

// Constructors
TEST(Map, base_constructor) {
  s21::Map<int, int> map;
  ASSERT_TRUE(map.size() == 0);
}

TEST(Map, initializer_list) {
  s21::Map<int, char> map{
      std::pair<int, char>{4, 'a'}, std::pair<int, char>{2, 'b'},
      std::pair<int, char>{3, 'c'}, std::pair<int, char>{7, 'd'}};
  ASSERT_TRUE(map.size() == 4);
  ASSERT_TRUE(map.at(4) == 'a');
  ASSERT_TRUE(map.at(7) == 'd');
}

TEST(Map, copy_constructor) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}, std::pair<int, char>{6, 'f'},
      std::pair<int, char>{8, 'g'}};
  s21::Map<int, char> map2(map);
  ASSERT_TRUE(map2.size() == 7);
  ASSERT_TRUE(map2.at(5) == 'a');
  ASSERT_TRUE(map2.at(8) == 'g');
  ASSERT_TRUE(map2.at(2) == 'd');
}

TEST(Map, move_constructor) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  s21::Map<int, char> map2(std::move(map));
  ASSERT_TRUE(map2.size() == 5);
  ASSERT_TRUE(map2.at(5) == 'a');
  ASSERT_TRUE(map2.at(7) == 'c');
  ASSERT_TRUE(map2.at(2) == 'd');
}

TEST(Map, move_operator) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  s21::Map<int, char> map2 = std::move(map);
  ASSERT_TRUE(map2.size() == 5);
  ASSERT_TRUE(map2.at(5) == 'a');
  ASSERT_TRUE(map2.at(7) == 'c');
  ASSERT_TRUE(map2.at(2) == 'd');
}

TEST(Map, accessor_inserter_element_operator) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  ASSERT_TRUE(map.size() == 5);
  ASSERT_TRUE(map[5] == 'a');
  ASSERT_TRUE(map[7] == 'c');
  ASSERT_TRUE(map[2] == 'd');
  map[2] = 'g';
  ASSERT_TRUE(map[2] == 'g');
}

TEST(Map, begin) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'}};
  ASSERT_TRUE(map.begin().getNode()->key == 2);
}

TEST(Map, end) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'}};
  ASSERT_TRUE(map.end().getNode() == nullptr);
}

TEST(Map, empty) {
  s21::Map<int, char> map;
  ASSERT_TRUE(map.empty() == true);
  s21::Map<int, char> map2{std::pair<int, char>{5, 'a'}};
  ASSERT_TRUE(map2.empty() == false);
}

TEST(Map, max_size) {
  s21::Map<int, char> map;
  ASSERT_TRUE(map.max_size());
}

// Modifiers
TEST(Map, clear) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'}};
  map.clear();
  ASSERT_TRUE(map.size() == 0);
}

// TEST(Map, insert_pair_max_size) {
//   s21::Map<int, int> map;
//   map.insert(std::make_pair(3, 10));
//   map.insert(std::make_pair(4, 40));
//   map.insert(std::make_pair(5, 50));
//   map.insert(std::make_pair(6, 60));
//   map.insert(std::make_pair(7, 70));
//   ASSERT_TRUE(map.at(7) == 70);
//   std::pair<s21::BTree<int, int>::iterator, bool> result =
//   map.insert(std::make_pair(8, 80)); ASSERT_TRUE(result.second == false);
// }

TEST(Map, insert_pair) {
  s21::Map<int, int> map;
  map.insert(std::make_pair(3, 10));
  ASSERT_TRUE(map.at(3) == 10);
}

TEST(Map, insert_key_value) {
  s21::Map<int, char> map;
  map.insert(3, 'a');
  map.insert(2, 'b');
  ASSERT_TRUE(map.at(3) == 'a');
  ASSERT_TRUE(map.at(2) == 'b');
}

TEST(Map, insert_or_assign_key_value) {
  s21::Map<int, char> map;
  map.insert(3, 'a');
  ASSERT_TRUE(map.at(3) == 'a');
  map.insert_or_assign(2, 'c');
  ASSERT_TRUE(map.at(2) == 'c');
  map.insert_or_assign(2, 'G');
  ASSERT_TRUE(map.at(2) == 'G');
}

TEST(Map, erase_no_child) {
  s21::Map<int, char> map;
  map.insert(7, 'a');
  map.insert(3, 'b');
  map.erase(map.find(3));
  ASSERT_TRUE(map.size() == 1);
  ASSERT_FALSE(map.contains(3));
}

TEST(Map, erase_one_child) {
  s21::Map<int, char> map;
  map.insert(7, 'a');
  map.insert(3, 'b');
  map.insert(8, 'c');
  map.insert(2, 'd');
  map.erase(map.find(3));
  ASSERT_TRUE(map.size() == 3);
  ASSERT_TRUE(map.contains(3) == false);
  ASSERT_TRUE(map.find(7).getNode()->left->key == 2);
}

TEST(Map, erase_two_child) {
  s21::Map<int, char> map;
  map.insert(7, 'a');
  map.insert(3, 'b');
  map.insert(8, 'c');
  map.insert(2, 'd');
  map.insert(4, 'e');
  map.erase(map.find(3));
  ASSERT_TRUE(map.size() == 4);
  ASSERT_TRUE(map.contains(3) == false);
}

TEST(Map, erase_two_child_2) {
  s21::Map<int, char> map;
  map.insert(8, 'a');
  map.insert(4, 'b');
  map.insert(11, 'c');
  map.insert(2, 'd');
  map.insert(6, 'e');
  map.insert(9, 'e');
  map.insert(12, 'e');
  map.insert(1, 'e');
  map.insert(3, 'e');
  map.insert(5, 'e');
  map.insert(7, 'e');
  map.insert(10, 'e');
  map.erase(map.find(4));
  ASSERT_TRUE(map.size() == 11);
  ASSERT_TRUE(map.contains(4) == false);
}

TEST(Map, merge) {
  s21::Map<int, char> s21_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  s21::Map<int, char> s21_map2{{1, 'd'}, {10, 'e'}, {11, 'f'}};
  s21_map.merge(s21_map2);
  ASSERT_TRUE(s21_map.size() == 5);
}

TEST(Map, braces_empty) {
  s21::Map<int, char> s21_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  std::map<int, char> std_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  EXPECT_EQ(s21_map[0], std_map[0]);
}

TEST(Map, insert_many) {
  s21::Map<int, int> map;
  auto result = map.insert_many(std::make_pair(3, 40), std::make_pair(5, 50),
                                std::make_pair(10, 60), std::make_pair(16, 70));
  ASSERT_EQ(map.size(), 4);
  ASSERT_EQ(map.find(3).getNode()->value, 40);
  ASSERT_EQ(map.find(5).getNode()->value, 50);
  ASSERT_EQ(map.find(10).getNode()->value, 60);
  ASSERT_EQ(map.find(16).getNode()->value, 70);

  ASSERT_EQ(result.at(0).first.getNode()->value, 40);
  ASSERT_EQ(result.at(1).first.getNode()->value, 50);
  ASSERT_EQ(result.at(2).first.getNode()->value, 60);
  ASSERT_EQ(result.at(3).first.getNode()->value, 70);
  ASSERT_EQ(result.at(0).second, true);
}

TEST(Map, iter_ptr) {
  s21::Map<int, int> map;
  auto it = map.begin();
  ASSERT_TRUE((++it) == map.begin());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
