#include <list>
#include <iostream>
#include <string>
#include "./s21_list.h"

using namespace std;

int main() {
    list<std::string> test;
    test.push_back("aboba");
    test.push_back("asdf");
    test.push_front("gfds");
    for (auto iter = test.begin(); iter != test.end(); ++iter)
        std::cout << *(test.insert(iter, "insert")) << std::endl;
        //        std::cout << *iter << std::endl;
    std::cout << std::endl;
    for (auto iter = test.begin(); iter != test.end(); ++iter)
        std::cout << *iter << std::endl;
    return 0;
}

