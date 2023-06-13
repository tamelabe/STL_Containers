<<<<<<< HEAD
/**
Copyright 2023 darrpama@student.21-school.ru, myregree@student.21-school.ru

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#include "s21_tree.h"
=======
#include "helpers/BinaryTree.h"
>>>>>>> 4e19fc7a8e4cdb8bf0807f757cd0e2021d94dbae

namespace s21 {

template<typename Key>
class set {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<key_type>;
  using const_iterator = SetConstIterator<key_type>;
  using size_type = size_t;

public:
  set();
// | set(std::initializer_list<value_type> const &items);
// | set(const set &s);
// | set(set &&s);
// | ~set();
// | operator=(set &&s);

  // iterator begin();
  // iterator end();

  // bool empty();
  // size_type size();
  // size_type max_size();

  // void clear();
  // std::pair<iterator, bool> insert(const value_type& value);
  // void erase(iterator pos);
  // void swap(set& other);
  // void merge(set& other);

  // iterator find(const Key& key);
  // bool contains(const Key& key);

private:
  s21::BSTree<Key> tree_;

};

template <typename Key>
s21::set<Key>::set() {}

}
// mintimir izvrachenec - on lubit VIM