#include "./s21_list.h"

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <cassert>




struct President
{
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }

    President(President&& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }

    President& operator=(const President& other) = default;
};

int main()
{

    s21::List<President> elections;
    std::cout << "emplace_back:\n";
    auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);
    assert(ref.year == 1994 && "uses a reference to the created object (C++17)");

    s21::List<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const& president: elections)
        std::cout << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";

    for (President const& president: reElections)
        std::cout << president.name << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    return 0;
}





////template <typename T>
//void printList(s21::List<T>& a) {
//  for (auto iter = a.begin(); iter != a.end(); ++iter) {
//    std::cout << *iter << " ";
//  }
//  std::cout << std::endl;
//}
//template <typename T>
//void printList(std::list<T>& a) {
//  for (auto iter = a.begin(); iter != a.end(); ++iter) {
//    std::cout << *iter << " ";
//  }
//  std::cout << std::endl;
//}
//// template <typename T>
//// void printRevList(std::ist<T>& a) {
////   for (auto iter = --a.end(); iter != a.begin(); --iter) {
////     std::cout << *iter << " ";
////   }
////   std::cout << *a.begin() << std::endl;
//// }
//
//int main() {
//  s21::List<std::node> s21_test{"aboba", "asdf"};
//  std::list<std::string> std_test{"aboba", "asdf"};
//  s21_test.pop_back();
//  std_test.pop_back();
//  std_test.emplace(std_test.begin(), "asdf", "asdf");
//  printList(s21_test);
//  printList(std_test);
//  return 0;
//}
