//
// Created by fedya on 10.02.18.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include "structure.h"


class Stack : public Structure {
public:
    using Structure::Structure;

    int pop(int *value);

    int push(int value);

    void dump(unsigned) override;

    void dump();

    int ok() override;
};

#endif //STACK_STACK_H
