#include <list>
#include <iostream>
#include "./s21_list.h"

using namespace std;

int main() {
    list<int> mylist = {1, 2, 2, 3, 2};
    mylist.push_back(5);
    mylist.push_back(567);
    mylist.sort();
    mylist.unique();
    mylist.reverse();
    auto i = mylist.begin();
    for (i; i != mylist.end(); ++i)
        cout << *i << endl;
    return 0;
}

