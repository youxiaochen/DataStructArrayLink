//
// Created by You on 2018/6/5.
//
#include "Log.h"
class Dog {

public:

    char *name;

    int age;

    Dog(char *name, int age) {
        this->age = age;
        this->name = name;
        LOGD("construct Dog %s %d ", name, age);
    }

    Dog(const Dog& d) {
        this->age = d.age;
        this->name = d.name;
        LOGD("copy Dog %s %d", name,  age);
    }

    ~Dog(){
        LOGD("~~~Dog %s %d", name, age);
    }

};
