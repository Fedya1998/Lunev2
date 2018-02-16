//
// Created by fedya on 10.02.18.
//

#ifndef STACK_ITER_H
#define STACK_ITER_H

#include "stack.h"

class Iterator {
public:
    int error = 0;
//private:
    int counter;
    Structure &structure;
public:
    enum Errors {
        COUNTER_PROBLEMS,
        NEXT_PROBLEMS,
        FIRST_PROBLEMS,
        FINISH_PROBLEMS
    };

    explicit Iterator(Structure &structure);

    void next();

    int *first();

    bool finish();

    const int *get();


};


#endif //STACK_ITER_H
