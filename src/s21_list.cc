#include "./s21_list.h"

#include <iostream>
#include <list>
#include <string>
#include <utility>

using namespace s21;

template <typename T>
void printList(List<T>& a) {
  for (auto iter = a.begin(); iter != a.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
template <typename T>
void printRevList(List<T>& a) {
  for (auto iter = --a.end(); iter != a.begin(); --iter) {
    std::cout << *iter << " ";
  }
  std::cout << *a.begin() << std::endl;
}

int main() {
  //    List<int> mrg1 = {4, 3, 2, 1, -1, -50, 100};
  //    List<int> mrg2 = {4, 7, 6};
  //    auto iter = mrg1.begin();
  //    mrg1.sort();
  List<int> mrg3 = {1, 2, 3, 4};
  mrg3 = std::move(mrg3);
  printList(mrg3);
  //    mrg2.sort();
  //    printList(mrg1);
  //    printRevList(mrg1);
  //    printList(mrg2);
  return 0;
}
