#include "../s21_map.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

// Constructors
TEST(Constructor, base) {
  s21::map<int, int> map;
  map.insert(std::make_pair(1, 10));
  // map.insert(std::make_pair(2, 20));
  // map.insert(std::make_pair(3, 30));
  // map.insert(std::make_pair(4, 40));
  // map.insert(std::make_pair(5, 50));

  // map.print_map();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
