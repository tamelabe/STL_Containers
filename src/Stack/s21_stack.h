#ifndef CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_

#include "../List/s21_list.h"
#include <initializer_list>

namespace s21 {
template <class T, class Container = s21::List<T>>
        class Stack {
public:
    // Aliases declaration
    using container_type = Container;
    using value_type = typename Container::value_type;
    using const_reference = typename Container::const_reference;
    using size_type = typename Container::size_type;


    Stack() : container_() {}
    Stack(std::initializer_list<value_type> const &items) : container_(items) {}
    Stack(const Stack &s) : container_(s.container_) {}
    Stack(Stack &&s) : container_(std::move(s.container_)) {}
    ~Stack() {}

    Stack &operator=(const Stack &s) {
        container_ = s.container_;
        return *this;
    }
    Stack &operator=(Stack &&s) {
        container_ = s.container_;
        return *this;
    }

    const_reference top() {
        return;
    }
    bool empty();
    size_type size();
    void push(const_reference value) {
        cont
    }
    void pop();
    void swap(Stack& other);

    template<class... Args>
    iterator emplace_front(Args &&...args);

private:
    Container container_;
};
}  // namespace s21

#endif // CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_