#include <jni.h>
#include <string>
#include "Log.h"

using namespace std;

#include "Dog.cpp"
#include "LinkedList.hpp"
#include "ArrayList.hpp"
#include "ArrayStack.hpp"
#include "LinkedStack.hpp"
#include "ArrayDeque.hpp"
#include "PriorityQueue.hpp"
#include "HeapSort.cpp"
#include "BlockingQueue.hpp"

#include <pthread.h>
#include <unistd.h>

extern "C" {


    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test0(JNIEnv *env, jobject /* this */) {
        List<Dog*> *list = new ArrayList<Dog*>();
        Dog *dog1 = new Dog("dog1*", 11);
        Dog *dog2 = new Dog("dog2*", 22);
        Dog *dog3 = new Dog("dog3*", 33);
        list->add(dog1);
        list->add(dog3);
        list->add(1, dog2);
        list->remove(2);
        for (int i = 0; i < list->size(); ++i) {
            Dog *dog = list->get(i);
            LOGD("Dog %s, %d", dog->name, dog->age);
        }
        delete list; delete dog1; delete dog2; delete dog3;

        LOGD("------divider--------- \n\n\n");

        ArrayList<Dog> dogs1;
        dogs1.add(Dog{"dog1",  13 });
        dogs1.add(Dog{"dog2",  25 });
        Dog d1 = {"dog3", 38};
        dogs1.add(d1);
        dogs1.remove(1);

        for (int i = 0; i < dogs1.size(); ++i) {
            Dog dog = dogs1.get(i);
            LOGD("Dog %s, %d", dog.name, dog.age);
        }
        dogs1.clear();
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test1(JNIEnv *env, jobject /* this */) {
        List<Dog*> *list = new LinkedList<Dog*>();
        Dog *dog1 = new Dog("dog1*", 11);
        Dog *dog2 = new Dog("dog2*", 22);
        Dog *dog3 = new Dog("dog3*", 33);
        list->add(dog1);
        list->add(dog3);
        list->add(1, dog2);
        list->remove(2);
        for (int i = 0; i < list->size(); ++i) {
            Dog *dog = list->get(i);
            LOGD("Dog %s, %d", dog->name, dog->age);
        }
        delete list; delete dog1; delete dog2; delete dog3;

        LOGD("------divider--------- \n\n\n");

        LinkedList<Dog> dogs1;
        dogs1.add(Dog{"dog1",  13 });
        dogs1.add(Dog{"dog2",  25 });
        Dog d1 = {"dog3", 38};
        dogs1.add(d1);
        dogs1.remove(1);

        for (int i = 0; i < dogs1.size(); ++i) {
            Dog dog = dogs1.get(i);
            LOGD("Dog %s, %d", dog.name, dog.age);
        }
        dogs1.clear();
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test2(JNIEnv *env, jobject /* this */) {
        Stack<Dog*> *stack = new ArrayStack<Dog*>();
        Dog *dog1 = new Dog("dog1*", 11);
        Dog *dog2 = new Dog("dog2*", 22);
        Dog *dog3 = new Dog("dog3*", 33);
        stack->push(dog1);
        stack->push(dog2);
        stack->push(dog3);
        stack->pop();
        while (!stack->isEmpty()) {
            Dog *dog = stack->pop();
            LOGD("Dog %s, %d", dog->name, dog->age);
        }
        delete stack; delete dog1; delete dog2; delete dog3;

        ArrayStack<Dog> dogs1;
        dogs1.push(Dog{"dog1",  13 });
        dogs1.push(Dog{"dog2",  25 });
        Dog d1 = {"dog3", 38};
        dogs1.push(d1);
        dogs1.pop();

        while (!dogs1.isEmpty()) {
            Dog dog = dogs1.pop();
            LOGD("Dog %s, %d", dog.name, dog.age);
        }
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test3(JNIEnv *env, jobject /* this */) {
        Stack<Dog*> *stack = new LinkedStack<Dog*>();
        Dog *dog1 = new Dog("dog1*", 11);
        Dog *dog2 = new Dog("dog2*", 22);
        Dog *dog3 = new Dog("dog3*", 33);
        stack->push(dog1);
        stack->push(dog2);
        stack->push(dog3);
        stack->pop();
        while (!stack->isEmpty()) {
            Dog *dog = stack->pop();
            LOGD("Dog %s, %d", dog->name, dog->age);
        }
        delete stack; delete dog1; delete dog2; delete dog3;

        LinkedStack<Dog> dogs1;
        dogs1.push(Dog{"dog1",  13 });
        dogs1.push(Dog{"dog2",  25 });
        Dog d1 = {"dog3", 38};
        dogs1.push(d1);
        dogs1.pop();

        while (!dogs1.isEmpty()) {
            Dog dog = dogs1.pop();
            LOGD("Dog %s, %d", dog.name, dog.age);
        }
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test4(JNIEnv *env, jobject /* this */) {
        ArrayDeque<Dog*> *deque = new ArrayDeque<Dog*>();
        Dog *dog1 = new Dog("dog1*", 11);
        Dog *dog2 = new Dog("dog2*", 22);
        Dog *dog3 = new Dog("dog3*", 33);
        deque->push(dog2);
        deque->push(dog3);
        deque->pushFront(dog1);

        Dog *d = deque->popBack();
        LOGD("Dog %s, %d", d->name, d->age);
        while (!deque->isEmpty()) {
            Dog *dog = deque->pop();
            LOGD("Dog %s, %d", dog->name, dog->age);
        }
        delete deque; delete dog1; delete dog2; delete dog3;
    }

    struct DogCompare {

        bool operator() (const Dog *left, const Dog *right) {
            return left->age > right->age;
        }

    };

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test5(JNIEnv *env, jobject /* this */) {
        PriorityQueue<Dog*, DogCompare> *queue = new PriorityQueue<Dog*, DogCompare>();
        Dog *d1 = new Dog("Dog1", 15);
        Dog *d2 = new Dog("Dog2", 52);
        Dog *d3 = new Dog("Dog3", 35);
        Dog *d4 = new Dog("Dog4", 41);
        Dog *d5 = new Dog("Dog5", 99);
        Dog *d6 = new Dog("Dog6", 20);
        Dog *d7 = new Dog("Dog7", 11);
        Dog *d8 = new Dog("Dog8", 19);

        queue->push(d1);
        queue->push(d2);
        queue->push(d3);
        queue->push(d4);
        queue->push(d5);
        queue->push(d6);
        queue->push(d7);
        queue->push(d8);

        while (!queue->isEmpty()) {
            Dog *dog = queue->poll();
            LOGD("Dog %s, %d", dog->name, dog->age);
        }
        delete queue; delete d1; delete d2; delete d3; delete d4; delete d5; delete d6; delete d7; delete d8;
    }

    JNIEXPORT void JNICALL
    Java_you_chen_ctest_MainActivity_test6(JNIEnv *env, jobject /* this */) {
        int arrs[] = {12, 4, 23, 99, 56, 78, 41, 31, 52, 1, 46, 19, 85, 88, 3, 8, 10};
        int len = sizeof(arrs) / sizeof(int);
        HeapSort::sort(arrs, len);
        string str;
        for (int i = 0; i < len; ++i) {
            str += to_string(arrs[i]);
            str += "  ";
        }
        LOGD("%s  ", str.c_str());
    }

}

