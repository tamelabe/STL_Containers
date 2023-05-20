#include "s21_Vector.h"
#include "test_utils.h"
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

TEST(Constructors, base) {
    EXPECT_TRUE(std::is_default_constructible<std::vector<int>>::value);
    EXPECT_TRUE(std::is_default_constructible<s21_Vector<int>>::value);
}


TEST(Constructors, with_parameter) {
    s21_Vector vec = s21_Vector(2);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
