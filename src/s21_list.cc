#include <list>
#include <iostream>
#include <string>
#include "./s21_list.h"

using namespace s21;

template <typename T>
void printList(list<T>& a) {
    for (auto iter = a.begin(); iter != a.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

int main() {
//    list<int> test;
//    test.push_back(3);
//    test.push_back(2);
//    test.push_back(1);
//    test.push_back(4);
//    test.push_back(10);
//    std::cout << std::endl;
//    for (auto iter = test.begin(); iter != test.end(); ++iter)
//        std::cout << *iter << std::endl;
//
//    test.sort();
//    std::cout << "After sorting:" << '\n';
//    for (auto iter = test.begin(); iter != test.end(); ++iter)
//        std::cout << *iter << std::endl;

//    list<int> a = {1, 2, 3};
//    printList(a);
//    list<int> b = {4, 8, 12};
//    printList(b);
//    a.merge(b);
//    printList(a);

//    list<int> empty {1, 2, 3};
    list<std::string> empty;
    empty.push_back("3");
    empty.push_back("2");
    empty.push_back("1");
//    empty.pop_front();
//    empty.pop_front();
//    empty.pop_front();
    std::cout << empty.back() << std::endl;

    return 0;
}

