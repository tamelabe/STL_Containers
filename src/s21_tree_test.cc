#include "s21_map.h"

// #include <gtest/gtest-spi.h>
// #include <gtest/gtest.h>

#include <iostream>

// TEST(Constructors, default_) {
//   s21::Node<std::pair<int, int>>;
// }

int main(int argc, char** argv) {



  s21::map<char, int> m;

  m.insert(std::make_pair('I', 0));
  m.insert(std::make_pair('A', 0));
  m.insert(std::make_pair('X', 10));

  std::pair<char, int> needle = m.find(std::make_pair('I', 0));


  // s21::BSTree<std::string, int> aboba;
  // aboba.insert("3", 3);
  // aboba.insert("1", 1);
  // aboba.insert("2", 2);
  // aboba.insert("4", 3);
  // aboba.insert("0", 3);
  // aboba.printBT(aboba);

  // ::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();
}
