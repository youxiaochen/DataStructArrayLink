//
// Created by You on 2018/6/1.
//

#ifndef CTEST_LIST_HPP
#define CTEST_LIST_HPP

#define NULL 0

template <class E>
class List {

protected:
	int len = 0;

public:
	virtual ~List();
	virtual int size();
	virtual bool isEmpty();
	//清空
	virtual void clear() = 0;
	//添加
	virtual bool add(const E &e) = 0;
	virtual bool add(int index, const E &e) = 0;
	//移除
	virtual E remove(int index) = 0;
	virtual E get(int index) = 0;
};

template <class E>
List<E>::~List() {
}

template <class E>
int List<E>::size() {
	return len;
}

template <class E>
bool List<E>::isEmpty() {
	return len <= 0;
}

#endif //CTEST_LIST_HPP
