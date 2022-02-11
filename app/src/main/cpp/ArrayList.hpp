//
// Created by You on 2018/6/1.
//

#ifndef CTEST_ARRAYLIST_HPP
#define CTEST_ARRAYLIST_HPP

#include <assert.h>
#include <malloc.h>
#include "List.hpp"

template <class E>
class ArrayList : public List<E> {

private:
    /**
     * 初始化数组大小
     */
    int data_size = 0;
    E *datas = NULL;

    void ensureCapacityInternal(int minCapacity);
    //扩充
    void grow(int minCapacity);

public:

    ArrayList();
    ArrayList(int initialCapacity);
    ~ArrayList();

    void clear();
    bool add(const E &e);
    bool add(int index, const E &e);
    E remove(int index);
    E get(int index);
};

//默认大小10
template <class E>
ArrayList<E>::ArrayList() {
}

template <class E>
ArrayList<E>::ArrayList(int initialCapacity) {
    assert(initialCapacity > 1);
    this->data_size = initialCapacity;
    this->datas = (E*) malloc(sizeof(E) * initialCapacity);
}

template <class E>
ArrayList<E>::~ArrayList() {
    if (this->datas) {
        free(this->datas);
        this->datas = NULL;
    }
}

/**
 * 这里忽略扩充数组后大小超过int最大值
 * @tparam E
 * @param index
 * @param e
 */
template <class E>
void ArrayList<E>::ensureCapacityInternal(int minCapacity) {
    if (this->datas == NULL) {
        minCapacity = 10; //默认10个大小
    }
    if (minCapacity > this->data_size) {
        grow(minCapacity);
    }
}

template <class E>
void ArrayList<E>::grow(int minCapacity) {
    int new_len = data_size + (data_size >> 1);
    if (new_len < minCapacity) {
        new_len = minCapacity;
    }
    E *new_datas = (E*) malloc(sizeof(E) * new_len);
    if (this->datas != NULL) {
        if (List<E>::len > 0) {
            // 拷贝数据
            memcpy(new_datas, this->datas, sizeof(E) * List<E>::len);
        }
        // 释放原来的内存
        free(this->datas);
    }
    this->datas = new_datas;
    this->data_size = new_len;
}

template <class E>
void ArrayList<E>::clear() {
    List<E>::len = 0;
}

template <class E>
bool ArrayList<E>::add(const E &e) {
    ensureCapacityInternal(List<E>::len + 1);
    this->datas[List<E>::len++] = e;
    return true;
}

template <class E>
bool ArrayList<E>::add(int index, const E &e) {
    assert(index >= 0 && index <= List<E>::len);
    ensureCapacityInternal(List<E>::len + 1);
    memmove(this->datas + index + 1, this->datas + index, sizeof(E) * (List<E>::len - index));
    this->datas[index] = e;
    List<E>::len++;
    return true;
}

template <class E>
E ArrayList<E>::remove(int index) {
    assert(index >= 0 && index < List<E>::len);
    E data = datas[index];
    int num_moved = List<E>::len - index - 1;
    if (num_moved > 0) {
        memmove(this->datas + index, this->datas + index + 1, sizeof(E) * num_moved);
    }
    List<E>::len--;
    return data;
}

template <class E>
E ArrayList<E>::get(int index) {
    assert(index >= 0 && index < List<E>::len);
    return datas[index];
}

#endif //CTEST_ARRAYLIST_HPP
