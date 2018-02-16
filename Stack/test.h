//
// Created by fedya on 16.02.18.
//

#ifndef STACK_TEST_H
#define STACK_TEST_H


class TestStack {
public:
    int test_resize();

    int test_memory();

    int test_iter();

    int test_pop();

    int test_push();

    int test_ok();

    int test_operator_br();

    int test_get_count();

    int test_dump();

    int spoil_capacity(Stack &stack, int value);

    int spoil_count(Stack &stack, int value);

    int * spoil_data_ptr(Stack &stack, int *value);

    int spoil_data(Stack &stack, int value, int offset);
};

#endif //STACK_TEST_H
