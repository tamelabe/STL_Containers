#include <list>
#include <iostream>
#include <string>
#include "./s21_list.h"

using namespace s21;

int main() {
    list<std::string> test;
    test.push_back("aboba");
    test.push_back("asdf");
    test.push_front("gfds");
//    std::cout << std::endl;
    for (auto iter = test.begin(); iter != test.end(); ++iter)
        std::cout << *iter << std::endl;
    auto iter = test.begin();
    ++iter;
    test.erase(iter);
//    test.push_back("aboba");
    std::cout << "After clearing:" << '\n';
    for (auto iter = test.begin(); iter != test.end(); ++iter)
        std::cout << *iter << std::endl;
    return 0;
}

