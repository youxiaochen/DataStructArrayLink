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
    int initialCapacity;
    E *datas = NULL;
    //扩充
    void grow(int index, const E &e);

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
ArrayList<E>::ArrayList() : ArrayList(10) {
}

template <class E>
ArrayList<E>::ArrayList(int initialCapacity) {
    assert(initialCapacity > 1);
    this->initialCapacity = initialCapacity;
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
void ArrayList<E>::grow(int index, const E &e) {
    initialCapacity += initialCapacity >> 1;//扩充成原先的1.5倍
    E *newDatas = (E*) malloc(sizeof(E) * initialCapacity);
    for (int i = 0; i < index; i++)
    {
        newDatas[i] = this->datas[i];
    }
    newDatas[index] = e;
    for (int i = index + 1; i <= List<E>::len; i++)
    {
        newDatas[i] = datas[i - 1];
    }
    free(this->datas);
    this->datas = newDatas;
    List<E>::len++;
}

template <class E>
void ArrayList<E>::clear() {
    List<E>::len = 0;
}

template <class E>
bool ArrayList<E>::add(const E &e) {
    return add(ArrayList<E>::size(), e);
}

template <class E>
bool ArrayList<E>::add(int index, const E &e) {
    assert(index >= 0 && index <= List<E>::len);
    if (List<E>::len == initialCapacity)
    {//需要扩充
        grow(index, e);
        return true;
    }
    for (int i = List<E>::len - 1; i >= index; i--) {
        datas[i + 1] = datas[i];
    }
    datas[index] = e;
    List<E>::len++;
    return true;
}

template <class E>
E ArrayList<E>::remove(int index) {
    assert(index >= 0 && index < List<E>::len);
    E data = datas[index];
    for (int i = index; i < List<E>::len - 1; i++)
    {
        datas[i] = datas[i + 1];
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
