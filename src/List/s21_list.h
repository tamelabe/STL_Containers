#ifndef CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_

#include <initializer_list>
#include <iterator>
#include <limits>

#include "./s21_iterator.h"
#include "./s21_node.h"

namespace s21 {
template <class T>
class List {
 public:
  // Aliases declaration
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using size_type = std::size_t;
  using const_reference = const value_type &;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;
  using node = Node<T>;
  using node_ptr = node *;

  // List Member functions
  /**
   * @brief default constructor, creates empty List and "fake" node
   */
  List() : begin_(nullptr), end_(new Node<value_type>), size_(0) {
    initList();
  };
  /**
   * @brief parameterized constructor
   * @param creates the List of size n
   */
  explicit List(size_type n) : List() {
    for (size_type i = 0; i < n; ++i) push_back(value_type{});
  }
  /**
   * @brief initializer List constructor, creates List initizialized using
   * std::initializer_list
   * @param items
   */
  List(std::initializer_list<value_type> const &items) : List() {
    for (auto i = items.begin(); i < items.end(); ++i) push_back(*i);
  }
  /**
   * @brief copy constructor
   * @param l - List to copy
   */
  List(const List &l) : List() {
    for (auto i = l.begin(); i != l.end(); ++i) push_back(*i);
  }
  /**
   * @brief move constructor
   * @param l - rvalue reference
   */
  List(List &&l) : begin_(l.begin_), end_(l.end_), size_(l.size_) {
    l.begin_ = l.end_ = nullptr;
    l.size_ = 0;
  }
  /**
   * @brief destructor
   */
  ~List() { deallocate(true); }

  List &operator=(const List &l) {
    if (&l == this) return *this;
    clear();
    for (auto i = l.begin(); i != l.end(); ++i) push_back(*i);
    return *this;
  }
  List &operator=(List &&l) {
    if (&l == this) return *this;
    clear();
    begin_ = l.begin_;
    end_ = l.end_;
    size_ = l.size_;
    return *this;
  }
  // List Element access
  /**
   * @brief Returns a reference to the first element in the container.
   * @return reference to the first element
   */
  const_reference front() {
    if (begin_ == end_) throw std::out_of_range("List is empty");
    return *(begin_->data_);
  }
  /**
   * @brief Returns a reference to the last element in the container.
   * @return reference to the last element.
   */
  const_reference back() {
    if (begin_ == end_) throw std::out_of_range("List is empty");
    return *(end_->prev_->data_);
  }

  // List Iterators
  /**
   * @brief returns an iterator to the beginning
   */
  iterator begin() noexcept { return iterator(end_->next_); }
  /**
   * @brief returns an const iterator to the beginning
   */
  const_iterator begin() const noexcept { return const_iterator(end_->next_); }
  /**
   * @brief returns an iterator to the end (next from the last element)
   */
  iterator end() noexcept { return iterator(end_); }
  /**
   * @brief returns an const iterator to the end (next from the last element)
   */
  const_iterator end() const noexcept { return const_iterator(end_); }

  // List Capacity
  /**
   * @brief Checks if the container has no elements
   * @return true if the container is empty, false otherwise
   */
  bool empty() const noexcept { return begin_ == end_; }
  /**
   * @brief The number of elements in the container.
   * @return the number of elements
   */
  size_type size() const noexcept { return size_; }
  /**
   * @brief Returns the maximum number of elements the container is able to hold
   * due to system or library implementation limitations
   * @return Maximum number of elements.
   */
  size_type max_size() const noexcept {
    return std::numeric_limits<difference_type>::max() / (sizeof(node));
  }

  // List Modifiers
  /**
   * @brief clears the contents
   */
  void clear() noexcept {
    deallocate(false);
    initList();
  }
  /**
   * @brief inserts element into concrete pos and returns the iterator that
   * points to the new element
   * @param pos position of iterator to push new element
   * @param value value to push in data field
   * @return iterator that points to the new element
   */
  iterator insert(iterator pos, const_reference value) {
    iterator ret_iter;
    if (pos == begin()) {
      push_front(value);
      ret_iter = begin();
    } else {
      node_ptr new_node = new node(pos.node_->prev_, pos.node_, value);
      pos.node_->prev_->next_ = new_node;
      pos.node_->prev_ = new_node;
      ret_iter = iterator(new_node);
      ++size_;
    }
    return ret_iter;
  }
  /**
   * @brief erases element at pos
   * @param pos - position of iterator
   */
  void erase(iterator pos) {
    if (!pos.node_->data_) return;
    if (pos == begin()) {
      pop_front();
    } else if (pos != end()) {
      node_ptr temp = pos.node_->prev_;
      temp->next_ = pos.node_->next_;
      pos.node_->next_->prev_ = temp;
      nodeDestroyer(pos.node_);
    }
  }
  /**
   * @brief adds an element to the end
   * @param value additional element
   */
  void push_back(const_reference value) {
    if (end_ == begin_) {
      pushFirstNode(value);
    } else {
      node_ptr new_node = new node(end_->prev_, end_, value);
      end_->prev_->next_ = new_node;
      end_->prev_ = new_node;
    }
    ++size_;
  }
  /**
   * @brief removes the last element
   */
  void pop_back() noexcept {
    if (!end_->prev_->data_) return;
    node_ptr tmp = end_->prev_;
    tmp->prev_->next_ = end_;
    end_->prev_ = tmp->prev_;
    nodeDestroyer(tmp);
    begin_ = end_->next_;
  }
  /**
   * @brief adds an element to the head
   * @param value additional element
   */
  void push_front(const_reference value) {
    if (end_ == begin_) {
      pushFirstNode(value);
    } else {
      node_ptr new_node = new node(end_, begin_, value);
      end_->next_ = new_node;
      begin_->prev_ = new_node;
      begin_ = new_node;
    }
    ++size_;
  }
  /**
   * @brief removes the first element
   */
  void pop_front() noexcept {
    if (!end_->prev_->data_) return;
    end_->next_ = begin_->next_;
    begin_->next_->prev_ = end_;
    nodeDestroyer(begin_);
    begin_ = end_->next_;
  }
  /**
   * @brief swaps the contents
   */
  void swap(List &other) noexcept {
    std::swap(begin_, other.begin_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }
  /**
   * @brief Merges two sorted lists into one
   * @param other - another container to merge
   */
  void merge(List &other) {
    if (&other == this || !other.size_) return;
    if (!size_) {
      swap(other);
      return;
    }
    auto node_ths = begin();
    auto node_oth = other.begin();
    for (; node_ths != end() || node_oth != other.end(); ++node_ths) {
      while (node_oth != other.end() &&
             (*node_ths > *node_oth || node_ths == end())) {
        iterator last_oth = sortCheck(node_oth, other.end());
        node_oth = insSubList(node_ths, node_oth, last_oth);
      }
    }
    size_ += other.size_;
    other.initList();
  }
  /**
   * @brief Transfers elements from one List to another.
   * @param pos element before which the content will be inserted
   * @param other another container to transfer the content from
   */
  void splice(const_iterator pos, List &other) noexcept {
    if (&other == this || !other.size_) return;
    auto end = other.end();
    --end;
    insSubList(pos, other.begin(), end);
    size_ += other.size_;
    other.initList();
  }
  /**
   * @brief Reverses the order of the elements in the container.
   */
  void reverse() noexcept {
    if (!size_) return;
    auto it = begin();
    for (int sz = size_; sz >= 0; --sz) {
      iterator temp = it;
      ++it;
      std::swap(temp.node_->next_, temp.node_->prev_);
    }
    begin_ = end_->next_;
  }
  /**
   * @brief Removes all consecutive duplicate elements from the container
   */
  void unique() {
    for (auto i = begin(); i != --end();)
      if (*i == *(++i)) erase(--i);
  }
  /**
   * @brief Merge Sort algorithm based onion brand principle
   */
  void sort() {
    if (!size_ || size_ == 1) return;
    begin_ = mergeSort(begin().node_);
    nodesPrevRepair();
  }
  /**
   * @brief inserts new elements into the container directly before pos
   * @tparam Args Parameter pack
   * @param pos iterator position
   * @param args variadic template parameter
   * @return iterator for last inserted elem
   */
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    auto iter = begin();
    /**
     * (); - lambda expression
     * [&] - type of capture (by reference)
     * {} - body of lambda expression
     * () - declares function parameters
     * ... - template parameter pack expansion operator
     */
    ([&] { iter = insert(pos, std::forward<T>(args)); }(), ...);
    return iter;
  }
  /**
   * @brief appends new elements to the end of the container
   */
  template <class... Args>
  void emplace_back(Args &&...args) {
    ([&] { push_back(std::forward<T>(args)); }(), ...);
  }

  /**
   * @brief appends new elements to the top of the container
   */
  template <class... Args>
  void emplace_front(Args &&...args) {
    ([&] { push_front(std::forward<T>(args)); }(), ...);
  }

 private:
  // Variables
  node_ptr begin_;
  node_ptr end_;
  size_type size_;

  // Methods
  /**
   * @brief Create connection of empty List nodes from end_ to begin_
   */
  void initList() {
    end_->next_ = end_;
    end_->prev_ = end_;
    begin_ = end_;
    size_ = 0;
  }
  /**
   * @brief Deallocator
   * @param mode false - deallocate all non fake nodes,
   *             true - fully deallocation
   * @param node - node to deallocate when mode 2 chosen
   */
  void deallocate(bool mode) {
    if (!end_) return;
    for (auto i = begin(); i != end(); ++i) nodeDestroyer(i.node_);
    if (mode) delete end_;
  }
  /**
   * Deallocator for separate node
   */
  void nodeDestroyer(node_ptr node) {
    delete node->data_;
    delete node;
    --size_;
  }
  /**
   * @brief Using when pushing node in empty List
   * @param value pushing value in data_ field
   */
  void pushFirstNode(const_reference value) {
    node_ptr new_node = new node(end_, end_, value);
    end_->prev_ = end_->next_ = new_node;
    begin_ = new_node;
  }
  /**
   * @brief Checks for descending sequence
   * @param current current iterator position
   * @param end end of List
   * @return last desc sequence iterator
   */
  iterator sortCheck(iterator current, const iterator &end) {
    auto start_pos = current;
    ++current;
    while (current.node_->next_ != end.node_ && *start_pos > *(current)) {
      ++current;
    }
    return current;
  }
  /**
   * @brief Inserts sublist between given iterators inclusive into main List
   * BEFORE given position
   * @param pos iterator position of main List
   * @param first iterator that defines first point of sublist
   * @param last iterator that defines last point of sublist
   * @return next iterator after last param
   */
  iterator insSubList(const_iterator pos, iterator first, iterator last) {
    iterator next = last;
    ++next;
    pos.node_->prev_->next_ = first.node_;
    first.node_->prev_ = pos.node_->prev_;
    pos.node_->prev_ = last.node_;
    last.node_->next_ = pos.node_;
    if (pos == begin()) begin_ = first.node_;
    return next;
  }
  /**
   * @brief main sort recursive function (via mergeSort method)
   * @param first - first node of the List or sublist
   * @return sorted single-linked List
   */
  node_ptr mergeSort(node_ptr first) {
    if (first->next_ == end_ || first == end_) return first;
    node_ptr second = splitList(first);
    first = mergeSort(first);
    second = mergeSort(second);
    return mergeNodes(first, second);
  }
  /**
   * @brief divides List to two separate List
   * (first = N / 2, sec = N / 2 + N % 2)
   * @param first first node of the List or sublist
   * @return first node of the second List
   */
  node_ptr splitList(node_ptr first) {
    node_ptr second = first;
    while (first->next_ != end_ && first->next_->next_ != end_) {
      first = first->next_->next_;
      second = second->next_;
    }
    node_ptr sec_begin = second->next_;
    second->next_ = end_;
    return sec_begin;
  }
  /**
   * @brief recursively merges sublists to single-linked asc. ordered List
   * @param first - first node of first sublist
   * @param second - first node of second sublist
   * @return merged or existing List
   */
  node_ptr mergeNodes(node_ptr first, node_ptr second) {
    if (first == end_) return second;
    if (second == end_) return first;
    if (*first->data_ < *second->data_) {
      first->next_ = mergeNodes(first->next_, second);
      return first;
    } else {
      second->next_ = mergeNodes(second->next_, first);
      return second;
    }
  }
  /**
   * @brief repairs prev pointer of the List (makes it double-linked)
   */
  void nodesPrevRepair() {
    for (auto iter = iterator(begin_); iter != end(); ++iter) {
      iter.node_->next_->prev_ = iter.node_;
    }
    end_->next_ = begin_;
  }
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_