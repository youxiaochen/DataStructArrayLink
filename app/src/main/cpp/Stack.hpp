//
// Created by You on 2018/6/1.
//

#ifndef CTEST_STACK_HPP
#define CTEST_STACK_HPP

template <class E>
class Stack {
protected:
    int len = 0;

public:
    virtual ~Stack();

    virtual int size();
    virtual bool isEmpty();

    //弹出
    virtual E pop() = 0;
    //获取栈顶不弹出
    virtual E peek() = 0;
    //栈中添加元素
    virtual bool push(const E &e) = 0;
};

template <class E>
Stack<E>::~Stack() {
}

template <class E>
int Stack<E>::size() {
    return len;
}

template <class E>
bool Stack<E>::isEmpty() {
    return len <= 0;
}

#endif //CTEST_STACK_HPP
