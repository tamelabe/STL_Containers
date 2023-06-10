#include "./s21_list.h"

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <cassert>








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
    s21_test.sort();
    printList(s21_test);
  return 0;
}
