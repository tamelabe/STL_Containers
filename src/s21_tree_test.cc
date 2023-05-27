#include "s21_tree.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <iostream>

TEST(Constructors, default_) {
  s21::BSTree<int, int> tree_1;
  tree_1.insert(10, 128);
  tree_1.insert(11, 256);
  tree_1.insert(9, 512);
  EXPECT_TRUE(tree_1.find(9) == 512);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
