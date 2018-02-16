//
// Created by fedya on 10.02.18.
//

#include "stack.h"
#include "iter.h"

Iterator::Iterator(Structure &structure) : structure(structure) {
    counter = 0;
}


void Iterator::next() {
    counter++;
}


int * Iterator::first() {
    return structure[0];
}

bool Iterator::finish() {
    return counter >= structure.get_count();
}

const int * Iterator::get() {
    return structure[counter];
}
