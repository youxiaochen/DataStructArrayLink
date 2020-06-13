//
// Created by 77991 on 2020/6/10.
//

#ifndef CTEST_PRIORITYQUEUE_HPP
#define CTEST_PRIORITYQUEUE_HPP

#include <assert.h>
#include <malloc.h>

template <class E>
struct Greater {

    constexpr bool operator() (const E &left, const E &right) const {
        return left > right;
    }

};

template <class E>
struct LessEqual {

    constexpr bool operator() (const E &left, const E &right) const {
        return left <= right;
    }

};

template <class E, class C = Greater<E> >
class PriorityQueue {
private:

    E *queue;
    //类似JDK中的Comparable
    C comparator;

    int len = 0;
    //初始数组大小
    int capacity = 11;
    /**
     * 扩充数组
     * @param minCapacity
     */
    void grow();
    /**
     * 从下往上调整根堆
     * @param index
     * @param v
     */
    void siftUp(int index, const E &e);
    /**
     * 从上往下调整根堆
     * @param index
     * @param v
     */
    void siftDown(int index, const E &e);

public:
    PriorityQueue();
    PriorityQueue(int capacity);
    ~PriorityQueue();

    //队列是否空
    bool isEmpty();
    /**
     * 优先队列中添加元素
     * @param e
     */
    void push(const E &e);

    /**
     * 弹出队首元素
     * @return
     */
    E poll();
    //不弹出,查看首元素
    E peek();
};

//默认大小11
template <class E, class C>
PriorityQueue<E, C>::PriorityQueue() : PriorityQueue(11) {
}

template <class E, class C>
PriorityQueue<E, C>::PriorityQueue(int capacity) {
    assert(capacity > 1);
    this->capacity = capacity;
    this->queue = (E*) malloc(sizeof(E) * capacity);
}

template <class E, class C>
PriorityQueue<E, C>::~PriorityQueue() {
    if (this->queue) {
        free(this->queue);
        this->queue = NULL;
    }
}

/**
 * 这里忽略扩充数组后大小超过int最大值
 * @tparam E
 * @tparam C
 * @param minCapacity
 */
template <class E, class C>
void PriorityQueue<E, C>::grow() {
    //扩充前的数组长度超过64时扩充1.5倍
    capacity = capacity + ((capacity < 64) ? (capacity + 2) : (capacity >> 1));
    queue = (E*) realloc(queue, sizeof(E) * capacity);
}

template <class E, class C>
void PriorityQueue<E, C>::siftUp(int index, const E &e) {
    int parentIndex;
    while (index > 0) {
        parentIndex = (index - 1) >> 1;//找出父节点的位置
        if (comparator(queue[parentIndex], e)) {//父节点大于该节点,跳出循环
            break;
        }
        queue[index] = queue[parentIndex];
        index = parentIndex;
    }
    queue[index] = e;
}

template <class E, class C>
void PriorityQueue<E, C>::siftDown(int index, const E &e) {
    while (index < len >> 1) {
        int maxChildIndex = (index << 1) + 1;//左孩子与右孩子比较得出最大孩子的位置
        int rightChildIndex = maxChildIndex + 1;
        if (rightChildIndex < len && comparator(queue[rightChildIndex], queue[maxChildIndex])) {
            maxChildIndex = rightChildIndex;
        }
        if (!comparator(queue[maxChildIndex], e)) {
            break;
        }
        queue[index] = queue[maxChildIndex];
        index = maxChildIndex;
    }
    queue[index] = e;
}


template <class E, class C>
bool PriorityQueue<E, C>::isEmpty() {
    return len <= 0;
}

template <class E, class C>
void PriorityQueue<E, C>::push(const E &e) {
    if (this->len >= capacity) {
        grow();
    }
    siftUp(this->len, e);
    this->len++;
}

template <class E, class C>
E PriorityQueue<E, C>::poll() {
    assert(len > 0);
    E max = queue[0];
    this->len--;
    if (this->len > 0) {
        siftDown(0, queue[len]);
    }
    return max;
}

template <class E, class C>
E PriorityQueue<E, C>::peek() {
    assert(len > 0);
    return queue[0];
}

#endif //CTEST_PRIORITYQUEUE_HPP
