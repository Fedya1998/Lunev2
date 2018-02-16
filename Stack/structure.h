//
// Created by fedya on 10.02.18.
//

#ifndef STACK_STRUCTURE_H
#define STACK_STRUCTURE_H


class Structure {
protected:
    int *data = nullptr;
    int capacity = 0;
    int count = 0;
    int error = 0;
public:
    enum Errors {
        OK,
        EMPTY,
        FULL,
        COUNT_PROBLEMS,
        DATA_PROBLEMS,
        CAPACITY_PROBLEMS,
        NULLPTR_PROBLEMS
    };

    Structure();

    explicit Structure(int capacity);

    ~Structure();

    virtual void dump(unsigned depth);

    virtual int ok();

    int *operator[](unsigned i);

    int get_count();

    int resize(int capacity);
};

#endif //STACK_STRUCTURE_H
