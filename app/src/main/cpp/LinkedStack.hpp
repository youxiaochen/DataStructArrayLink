//
// Created by You on 2018/6/2.
//

#ifndef CTEST_LINKEDSTACK_HPP
#define CTEST_LINKEDSTACK_HPP


#include <assert.h>
#include "Stack.hpp"

template <class E>
class LinkedStack : public Stack<E> {

private:

    struct Node {
        E data;
        Node *next = NULL;
        Node(const E &data, Node *next) : data(data) {
            this->next = next;
        }
    };

    Node *popNode = NULL;
public:
    ~LinkedStack();
    E pop();
    E peek();
    bool push(const E& e);
};

template <class E>
LinkedStack<E>::~LinkedStack() {
    if (this->popNode) {
        Node *curr = this->popNode;
        while (curr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        this->popNode = NULL;
    }
}

template <class E>
E LinkedStack<E>::pop() {
    assert(Stack<E>::len > 0 && this->popNode);
    Node *next = this->popNode->next;
    E data = this->popNode->data;
    delete this->popNode;
    this->popNode = next;
    Stack<E>::len--;
    return data;
}

template <class E>
E LinkedStack<E>::peek() {
    assert(Stack<E>::len > 0 && this->popNode);
    return this->popNode->data;
}

template <class E>
bool LinkedStack<E>::push(const E &e) {
    Node *newNode = new Node(e, this->popNode);
    this->popNode = newNode;
    Stack<E>::len++;
    return true;
}

#endif //CTEST_LINKEDSTACK_HPP
