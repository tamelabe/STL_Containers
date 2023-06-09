#include "./s21_list.h"

#include <iostream>
#include <list>
#include <string>
#include <utility>

using namespace std;

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
  s21::List<std::string> s21_test{"aboba", "asdf"};
  std::list<std::string> std_test{"aboba", "asdf"};
  s21_test.pop_back();
  std_test.pop_back();
  printList(s21_test);
  printList(std_test);
  return 0;
}
