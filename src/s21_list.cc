#include <list>
#include <iostream>
#include <string>
#include "./s21_list.h"

using namespace std;

template <typename T>
void printList(list<T>& a) {
    for (auto iter = a.begin(); iter != a.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

int main() {
    list<int> mrg1 = {};
    list<int> mrg2 = {4, 5, 6};
    auto iter = mrg1.begin();
    mrg1.erase(iter);
    printList(mrg1);
    printList(mrg2);
    return 0;
}

