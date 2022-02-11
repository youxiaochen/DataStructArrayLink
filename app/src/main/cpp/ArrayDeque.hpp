//
// Created by You on 2018/6/5.
//

#ifndef CTEST_ARRAYDEQUE_HPP
#define CTEST_ARRAYDEQUE_HPP

#include <assert.h>

template <class E>
class ArrayDeque {

private:
    static const int DEF_CAPACITY = 16;
    /**
     * 阀值
     */
    int initialCapacity;
    int len = 0;
    /**
     * 队列头位置与尾位置
     */
    int headIndex = 0;
    int backIndex = 0;

    E *datas;
    /**
     * 扩充数组
     */
    void grow();
public:
    ArrayDeque();
    ArrayDeque(int numElements);
    ~ArrayDeque();

    bool isEmpty();
    int size();
    /**
     * 从队列尾部添加
     */
    bool push(const E &e);
    /**
     * 弹出队首
     */
    E pop();
    /**
     * 取队首不弹出
     */
    E peek();

    /**
     * 从队列首部添加
     */
    bool pushFront(const E &e);
    /**
     * 弹出队尾数据
     */
    E popBack();
    E peekBack();
};

/**
 * 这里忽略扩充数组后大小超过int最大值
 * @tparam E
 */
template <class E>
void ArrayDeque<E>::grow() {
    int new_size = initialCapacity << 1;
    E *newDatas = (E*) malloc(sizeof(E) * new_size);
    int copyIndex = initialCapacity - backIndex;
    memcpy(newDatas, datas + backIndex, sizeof(E) * copyIndex);
    memcpy(newDatas + copyIndex, datas, sizeof(E) * backIndex);
    headIndex = 0;
    backIndex = initialCapacity;
    initialCapacity = new_size;
    free(this->datas);
    datas = newDatas;
}

template <class E>
ArrayDeque<E>::ArrayDeque() {
    initialCapacity = DEF_CAPACITY;
    this->datas = (E*) malloc(sizeof(E) * initialCapacity);
}

template <class E>
ArrayDeque<E>::ArrayDeque(int numElements) {
    if (numElements > DEF_CAPACITY) {
        initialCapacity = numElements;
        initialCapacity |= (initialCapacity >> 1);
        initialCapacity |= (initialCapacity >> 2);
        initialCapacity |= (initialCapacity >> 4);
        initialCapacity |= (initialCapacity >> 8);
        initialCapacity |= (initialCapacity >> 16);
        initialCapacity++;
    }
    this->datas = (E*) malloc(sizeof(E) * initialCapacity);
}

template <class E>
ArrayDeque<E>::~ArrayDeque() {
    if (this->datas) {
        free(this->datas);
        this->datas = NULL;
    }
}

template <class E>
bool ArrayDeque<E>::isEmpty() {
    return headIndex == backIndex;
}

template <class E>
int ArrayDeque<E>::size() {
    return this->len;
}

template <class E>
bool ArrayDeque<E>::push(const E &e) {
    headIndex = (headIndex - 1) & (initialCapacity - 1);
    datas[headIndex] = e;
    if (headIndex == backIndex) {//需要扩充
        grow();
    }
    this->len++;
    return true;
}

template <class E>
E ArrayDeque<E>::pop() {
    assert(this->len > 0);
    backIndex = (backIndex - 1) & (initialCapacity - 1);
    E data = datas[backIndex];
    this->len--;
    return data;
}

template <class E>
E ArrayDeque<E>::peek() {
    assert(this->len > 0);
    int popIndex = (backIndex - 1) & (initialCapacity - 1);
    return datas[popIndex];
}

template <class E>
bool ArrayDeque<E>::pushFront(const E &e) {
    datas[backIndex] = e;
    backIndex = (backIndex + 1) & (initialCapacity - 1);
    if (headIndex == backIndex) {//需要扩充
        grow();
    }
    this->len++;
    return true;
}

template <class E>
E ArrayDeque<E>::popBack() {
    assert(this->len > 0);
    E data = datas[headIndex];
    headIndex = (headIndex + 1) & (initialCapacity - 1);
    this->len--;
    return data;
}

template <class E>
E ArrayDeque<E>::peekBack() {
    assert(this->len > 0);
    return datas[headIndex];
}


#endif //CTEST_ARRAYDEQUE_HPP
