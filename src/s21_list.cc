#include <list>
#include <iostream>
#include <string>
#include "./s21_list.h"

using namespace s21;

int main() {
    list<int> test;
    test.push_back(5);
    test.push_back(10);
    std::cout << *(++test.begin()) << std::endl;
    return 0;
}

