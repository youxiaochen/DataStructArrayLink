//
// Created by You on 2018/6/1.
//

#ifndef CTEST_LINKEDLIST_HPP
#define CTEST_LINKEDLIST_HPP


#include <assert.h>
#include "List.hpp"

template <class E>
class LinkedList : public List<E> {

private:

    struct Node {
        E data;
        Node *prev = NULL;
        Node *next = NULL;
        Node(const E &data, Node *prev, Node *next) : data(data) {
            this->prev = prev;
            this->next = next;
        }
    };

    /**
     * 头结点
     */
    Node *head = NULL;
    /**
     * 尾结点
     */
    Node *last = NULL;
    /**
     * 位置点节
     */
    Node* node(int index);

public:
    /**
     * 实现父类方法
     */
    ~LinkedList();
    void clear();

    bool add(const E &e);
    bool add(int index, const E &e);

    E remove(int index);
    E get(int index);

    /**
     * 新增方法
     */
    void addFirst(const E &e);
    void addLast(const E &e);
    //移除
    E removeFirst();
    E removeLast();
    E getFirst();
    E getLast();
};

/**
 * 注意此处的写法要加上typename
 * @tparam E
 * @param index
 * @return
 */
template <class E>
typename LinkedList<E>::Node* LinkedList<E>::node(int index) {
    if (index < List<E>::len >> 1)
    {//小于一半的长度,从头部开始查找
        Node *curr = this->head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        return curr;
    }
    else {
        Node *curr = this->last;
        for (int i = List<E>::len - 1; i > index; i--) {
            curr = curr->prev;
        }
        return curr;
    }
}

template <class E>
LinkedList<E>::~LinkedList() {
    this->clear();
}

template <class E>
void LinkedList<E>::clear() {
    if (this->head)
    {
        Node *curr = this->head;
        while (curr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        this->head = NULL;
        this->last = NULL;
        List<E>::len = 0;
    }
}

template <class E>
bool LinkedList<E>::add(const E &e) {
    addLast(e);
    return true;
}

template <class E>
bool LinkedList<E>::add(int index, const E &e) {
    assert(index >= 0 && index <= List<E>::len);
    if (index == 0)
    {
        addFirst(e);
        return true;
    }
    if (index == List<E>::len)
    {
        addLast(e);
        return true;
    }
    Node *addPreNode = node(index - 1);
    Node *addNextNode = addPreNode->next;
    Node *new_node = new Node(e, addPreNode, addNextNode);
    addPreNode->next = new_node;
    addNextNode->prev = new_node;
    List<E>::len++;
    return true;
}

template <class E>
E LinkedList<E>::remove(int index) {
    assert(index >= 0 && index < List<E>::len);
    if (index == 0)
    {
        return removeFirst();
    }
    if (index == List<E>::len - 1)
    {
        return removeLast();
    }
    Node *removeNode = node(index);
    Node *removePreNode = removeNode->prev;
    Node *removeNextNode = removeNode->next;
    removePreNode->next = removeNextNode;
    removeNextNode->prev = removePreNode;
    E e = removeNode->data;
    delete removeNode;
    List<E>::len--;
    return e;
}

template <class E>
E LinkedList<E>::get(int index) {
    assert(index >= 0 && index < List<E>::len);
    Node *getNode = node(index);
    return getNode->data;
}

template <class E>
void LinkedList<E>::addFirst(const E &e) {
    Node *newNode = new Node(e, NULL, head);
    if (this->head)
    {
        this->head->prev = newNode;
        this->head = newNode;
    }
    else {
        this->last = newNode;
        this->head = newNode;
    }
    List<E>::len++;
}

template <class E>
void LinkedList<E>::addLast(const E &e) {
    Node *newNode = new Node(e, last, NULL);
    if (this->head)
    {
        this->last->next = newNode;
        this->last = newNode;
    }
    else {
        this->last = newNode;
        this->head = newNode;
    }
    List<E>::len++;
}

template <class E>
E LinkedList<E>::removeFirst() {
    assert(this->head);
    Node *removeNode = this->head;
    Node *headNextNode = removeNode->next;
    if (headNextNode)
    {//有多个结点
        headNextNode->prev = NULL;
        this->head = headNextNode;
    }
    else {//只有一个结点
        this->head = NULL;
        this->last = NULL;
    }
    E e = removeNode->data;
    delete removeNode;
    List<E>::len--;
    return e;
}

template <class E>
E LinkedList<E>::removeLast() {
    assert(this->last);
    Node *removeNode = this->last;
    Node *lastPreNode = removeNode->prev;
    if (lastPreNode)
    {//有多个结点
        lastPreNode->next = NULL;
        this->last = lastPreNode;
    }
    else {//只有一个结点
        this->head = NULL;
        this->last = NULL;
    }
    E e = removeNode->data;
    delete removeNode;
    List<E>::len--;
    return e;
}

template <class E>
E LinkedList<E>::getFirst() {
    assert(List<E>::len > 0);
    return this->head->data;
}

template <class E>
E LinkedList<E>::getLast() {
    assert(List<E>::len > 0);
    return this->last->data;
}

#endif //CTEST_LINKEDLIST_HPP
