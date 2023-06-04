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
template <typename T>
void printRevList(list<T>& a) {
    for (auto iter = --a.end(); iter != a.begin(); --iter) {
        std::cout << *iter << " ";
    }
    std::cout << *a.begin() << std::endl;
}

int main() {
    list<int> mrg1 = {4, 3, 2, 1, -1, -50, 100};
    list<int> mrg2 = {4, 7, 6};
    auto iter = mrg1.begin();
    mrg1.sort();
    std::cout << "End_cycle\n";
//    mrg2.sort();
    printList(mrg1);
    printRevList(mrg1);
//    printList(mrg2);
    return 0;
}

