//
// Created by You on 2018/6/3.
//
#ifndef CTEST_ARRAYSTACK_HPP
#define CTEST_ARRAYSTACK_HPP

#include <assert.h>
#include "Stack.hpp"

template <class E>
class ArrayStack : public Stack<E> {
private:
    int capacity = 10;
    E *datas = NULL;
public:
    ArrayStack();
    ~ArrayStack();
    E pop();
    E peek();
    bool push(const E &e);
};

template <class E>
ArrayStack<E>::ArrayStack() {
    this->datas = (E*) malloc(sizeof(E) * capacity);
}

template <class E>
ArrayStack<E>::~ArrayStack() {
    if (this->datas) {
        free(this->datas);
        this->datas = NULL;
    }
}

template <class E>
E ArrayStack<E>::pop() {
    assert(Stack<E>::len > 0);
    int index = Stack<E>::len - 1;
    E data = datas[index];
    Stack<E>::len--;
    return data;
}

template <class E>
E ArrayStack<E>::peek() {
    assert(Stack<E>::len > 0);
    return datas[Stack<E>::len - 1];
}

/**
 * 这里忽略扩充数组后大小超过int最大值
 * @tparam E
 * @param e
 * @return
 */
template <class E>
bool ArrayStack<E>::push(const E &e) {
    if (Stack<E>::len == capacity) //需要扩充
    {
        capacity += capacity >> 1;//扩充成原先的1.5倍
        this->datas = (E*) realloc(this->datas, sizeof(E) * capacity);
    }
    datas[Stack<E>::len] = e;
    Stack<E>::len++;
    return true;
}

#endif //CTEST_ARRAYSTACK_HPP
