#include "./s21_list.h"

#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <utility>

template <typename T>
void printList(s21::List<T>& a) {
  for (auto iter = a.begin(); iter != a.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
template <typename T>
void printList(std::list<T>& a) {
  for (auto iter = a.begin(); iter != a.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
// template <typename T>
// void printRevList(std::ist<T>& a) {
//   for (auto iter = --a.end(); iter != a.begin(); --iter) {
//     std::cout << *iter << " ";
//   }
//   std::cout << *a.begin() << std::endl;
// }

int main() {
  s21::List<int> s21_test{1, 9, -1, 5, 6, 7, 4, 6, -11, 33};
    s21::List<int> s21_test_1{1, 1, 1, 1, 1, 1};
    std::cout << "Before: " << s21_test.size() << " ";
    std::cout << s21_test_1.size() << '\n';
    auto iter = s21_test.begin();
    auto iter_1 = s21_test_1.begin();
    s21_test.insert(iter_1, 999);
    std::cout << "After: " <<  s21_test.size() << ' ';
    std::cout << s21_test_1.size() << '\n';
    printList(s21_test);
    printList(s21_test_1);

  return 0;
}
