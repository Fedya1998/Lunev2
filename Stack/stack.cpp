//
// Created by fedya on 10.02.18.
//

#include <iostream>
#include "stack.h"

int Stack::pop(int *value) {
    if (!value)
        return NULLPTR_PROBLEMS;
    else if (count > 0) {
        *value = *(data + count-- - 1);
        return OK;
    } else
        return EMPTY;
}

int Stack::push(int value) {
    if (count < capacity) {
        data[count++] = value;
        return OK;
    } else
        return FULL;
}

void Stack::dump(unsigned depth) {
    std::string tabulation;
    tabulation.insert(0, depth, '\t');
    std::cerr << tabulation << "Stack error " << ok() << " {\n";
    Structure::dump(depth + 1);
    std::cerr << tabulation << "}\n";
}

void Stack::dump() {
    dump(0);
}

int Stack::ok() {
    return Structure::ok();
}
