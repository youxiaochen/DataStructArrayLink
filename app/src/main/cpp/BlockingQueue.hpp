//
// Created by 77991 on 2021/1/7.
//

#ifndef LINUXTEST_BLOCKINGQUEUE_HPP
#define LINUXTEST_BLOCKINGQUEUE_HPP

#include <queue>
#include <mutex>
using namespace std;

struct InterruptedException : public logic_error {

    InterruptedException(const char *_s) : logic_error(_s) {
    }

};

template <class E>
class BlockingQueue {

private:
    queue<E> _queue;
    int capacity = INT_MAX;
    condition_variable takeVariable, putVariable;
    mutable mutex lock;

public:
    BlockingQueue();

    BlockingQueue(int capacity);

    E take() throw(InterruptedException);

    void put(const E &e) throw(InterruptedException);

    bool empty() const;

    unsigned int size() const;

    void pop();

    E back();

    E front();
};

template <class E>
BlockingQueue<E>::BlockingQueue() {
}

template <class E>
BlockingQueue<E>::BlockingQueue(int capacity) : capacity(capacity) {
}

template <class E>
E BlockingQueue<E>::take() throw(InterruptedException) {
    unique_lock<mutex> uniqueLock(lock);
    while (_queue.empty()) {
        takeVariable.wait(uniqueLock);
    }
    if (_queue.empty()) {
        throw InterruptedException("Empty wait interrupted");
    }
    E e = _queue.front();
    _queue.pop();
    putVariable.notify_one();
    return e;
}

template <class E>
void BlockingQueue<E>::put(const E &e) throw(InterruptedException) {
    unique_lock<mutex> uniqueLock(lock);
    while (_queue.size() >= capacity) {
        putVariable.wait(uniqueLock);
    }
    if (_queue.size() >= capacity) {
        throw InterruptedException("Empty wait interrupted");
    }
    _queue.push(e);
    takeVariable.notify_one();
}

template <class E>
bool BlockingQueue<E>::empty() const {
    lock_guard<mutex> lockGuard(mutex);
    return _queue.empty();
}

template <class E>
unsigned int BlockingQueue<E>::size() const {
    lock_guard<mutex> lockGuard(mutex);
    return _queue.size();
}

template <class E>
void BlockingQueue<E>::pop() {
    lock.lock();
    _queue.pop();
    lock.unlock();
}

template <class E>
E BlockingQueue<E>::back() {
    lock_guard<mutex> lockGuard(mutex);
    return _queue.back();
}

template <class E>
E BlockingQueue<E>::front() {
    lock_guard<mutex> lockGuard(mutex);
    return _queue.front();
}

#endif //LINUXTEST_BLOCKINGQUEUE_HPP
