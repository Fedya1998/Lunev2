//
// Created by fedya on 10.02.18.
//

#include <cstdlib>
#include <iostream>
#include "structure.h"
#include <string.h>

Structure::Structure(int capacity) : capacity(capacity) {
    data = static_cast<int *>(calloc(static_cast<size_t >(capacity), sizeof(*data)));
    if (!data)
        std::cout << "Calloc problems\n";
}

int *Structure::operator[](unsigned i) {
    int maybe = ok();
    if (maybe != OK) {
        error = maybe;
        return nullptr;
    }
    if (i > count - 1)
        return nullptr;
    return data + i;
}

Structure::~Structure() {
    free(data);
}

int Structure::ok() {
    if (!data)
        return DATA_PROBLEMS;
    else if (!capacity)
        return CAPACITY_PROBLEMS;
    else if (count < 0 || count > capacity)
        return COUNT_PROBLEMS;
    else if (!count)
        return EMPTY;
    else if (count == capacity)
        return FULL;
    else
        return OK;
}

void Structure::dump(unsigned depth) {
    std::string tabulation;
    tabulation.insert(0, depth, '\t');
    std::cerr << tabulation << "Structure {\n"
              << tabulation << "\tthis " << this << '\n'
              << tabulation << "\tdata " << data << '\n'
              << tabulation << "\tcapacity " << &capacity << '\n'
              << tabulation << "\tcount " << &count << '\n'
              << tabulation << "\t}\n";
}

int Structure::get_count() {
    return count;
}

int Structure::resize(int capacity) {
    int *old_data = data;
    auto new_data = static_cast<int *>(realloc(data, static_cast<size_t >(capacity) * sizeof(*data)));
    if (!new_data) {
        std::cout << "Realloc problems\n";
        return 1;
    }
    this->capacity = capacity;
    data = new_data;
    return 0;
}

Structure::Structure() {
    Structure(10);
}

