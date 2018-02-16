#include <iostream>

#include <sys/resource.h>

#include "stack.h"
#include "iter.h"
#include "test.h"


static const int STACK_MAX_TESTS = 9;
static const int TEST_SUCCESSFUL = 1;
static const int TEST_FAILED = 0;
static const int PAVLIASHWILLY = 0xC0C0;

int test_stack() ;

inline int fail_with_msg(const char *msg);

int main() {
    return test_stack();
}

int test_stack() {
    TestStack test;
    int tests_successful =
            test.test_memory()
            + test.test_resize()
            + test.test_dump()
            + test.test_get_count()
            + test.test_ok()
            + test.test_operator_br()
            + test.test_pop()
            + test.test_push()
            + test.test_iter();

    std::cout << tests_successful << " tests of " << STACK_MAX_TESTS << "passed\n";
    return EXIT_SUCCESS;
}

int TestStack::test_pop() {
    Stack stack(10);
    int val;
    if (stack.pop(nullptr) != Structure::NULLPTR_PROBLEMS)
        return fail_with_msg("Pop problems with nullptr\n");

    if (stack.pop(&val) != Structure::EMPTY)
        return fail_with_msg("Pop problems with empty stack\n");

    spoil_count(stack, 1);
    spoil_data(stack, 0xF1F0, 0);

    if (stack.pop(&val) != Structure::OK || val != 0xF1F0)
        return fail_with_msg("Pop problems with value\n");

    return TEST_SUCCESSFUL;
}

int TestStack::test_push() {
    Stack stack(10);
    if (stack.push(25) != Structure::OK)
        return fail_with_msg("Push problems\n");

    if (spoil_data(stack, 0, 0) != 25)
        return fail_with_msg("Push problems - wrong data\n");

    spoil_count(stack, 10);
    if (stack.push(25) != Structure::FULL)
        return fail_with_msg("Push problems to a full stack\n");

    return TEST_SUCCESSFUL;
}

int TestStack::test_ok() {
    Stack stack(10);
    stack.push(PAVLIASHWILLY);

    if (stack.ok() != Structure::OK)
        return fail_with_msg("Ok problems");

    int * data = spoil_data_ptr(stack, nullptr);
    if (stack.ok() != Structure::DATA_PROBLEMS)
        return fail_with_msg("Ok problems - data no problems\n");
    spoil_data_ptr(stack, data);

    int capacity = spoil_capacity(stack, 0);
    if (stack.ok() != Structure::CAPACITY_PROBLEMS)
        return fail_with_msg("Ok problems - capacity no problems\n");
    spoil_capacity(stack, capacity);

    int count = spoil_count(stack, -100);
    if (stack.ok() != Structure::COUNT_PROBLEMS)
        return fail_with_msg("Ok problems - count no problems\n");
    spoil_count(stack, 0);

    if (stack.ok() != Structure::EMPTY)
        return fail_with_msg("Ok problems - not empty\n");
    spoil_count(stack, capacity);

    if (stack.ok() != Structure::FULL)
        return fail_with_msg("Ok problems - not full\n");

    return TEST_SUCCESSFUL;
}

int TestStack::test_get_count() {
    Stack stack(10);
    spoil_count(stack, 20);
    if (stack.get_count() != 20)
        return fail_with_msg("Get count problems\n");
    return TEST_SUCCESSFUL;
}

int TestStack::test_operator_br() {
    Stack stack (10);
    stack.push(0xC01A);
    stack.push(0xCAFE);

    int * old_data = spoil_data_ptr(stack, nullptr);
    if (stack[0])
        return fail_with_msg("Operator [] problems - nullptr");
    spoil_data_ptr(stack, old_data);

    if (stack[3])
        return fail_with_msg("Operator [] problems - exceeded");

    if (*stack[0] != 0xC01A || *stack[1] != 0xCAFE)
        return fail_with_msg("Operator [] problems\n");

    return TEST_SUCCESSFUL;
}

int TestStack::test_dump() {
    Stack stack(10);
    stack.dump();
    return TEST_SUCCESSFUL;
}

int TestStack::spoil_capacity(Stack &stack, int value) {
    int ret = *reinterpret_cast<int *>(reinterpret_cast<char *>(&stack) + 16);
    *reinterpret_cast<int *>(reinterpret_cast<char *>(&stack) + 16) = value;                  //capacity = value
    return ret;
}

int TestStack::spoil_count(Stack &stack, int value) {
    int ret = *reinterpret_cast<int *>(reinterpret_cast<char *>(&stack) + 20);
    *reinterpret_cast<int *>(reinterpret_cast<char *>(&stack) + 20) = value;                  //count = value
    return ret;
}

int * TestStack::spoil_data_ptr(Stack &stack, int *value) {
    int *ret = *reinterpret_cast<int **>(reinterpret_cast<char *>(&stack) + 8);
    *reinterpret_cast<int **>(reinterpret_cast<char *>(&stack) + 8) = value;                  //data = value
    return ret;
}

int TestStack::spoil_data(Stack &stack, int value, int offset) {
    int ret = *(*reinterpret_cast<int **>(reinterpret_cast<char *>(&stack) + 8) + offset * 4);
    *(*reinterpret_cast<int **>(reinterpret_cast<char *>(&stack) + 8) + offset * 4) = value;  //data[offset] = value
    return ret;
}

int TestStack::test_iter() {
    Stack stack(10);

    int arr[] = {
            PAVLIASHWILLY,
            0xF00D,
            0xBEEF,
            0xC0DE
    };

    for (int value : arr)
        stack.push(value);

    Iterator iter(stack);
    int k = 0;

    for (iter.first(); not iter.finish(); iter.next()){
        if (*iter.get() != arr[k] || k++ > 3)
            return fail_with_msg("Iterator problems");
    }
    return TEST_SUCCESSFUL;
}

int TestStack::test_memory() {//RLIMIT_DATA
    struct rlimit rlim = {};
    struct rlimit rlim2 = {1024, 1024};
    getrlimit(RLIMIT_DATA, &rlim);
    setrlimit(RLIMIT_DATA, &rlim2);

    int calloc_fail = 0;

    for (int i = 0; i < 40000; i++){
        Stack stack(i);
        int * old_data = spoil_data_ptr(stack, reinterpret_cast<int *>(9999));
        if (!old_data)
            calloc_fail++;
        spoil_data_ptr(stack, old_data);

    }
    setrlimit(RLIMIT_DATA, &rlim);

    if (!calloc_fail)
        return TEST_FAILED;

    return TEST_SUCCESSFUL;
}

int TestStack::test_resize() {
    struct rlimit rlim = {};
    struct rlimit rlim2 = {1024, 1024};
    getrlimit(RLIMIT_DATA, &rlim);
    setrlimit(RLIMIT_DATA, &rlim2);

    int realloc_fail = 0;

    Stack stacks [20000] = {};
    for (auto &stack : stacks) {
        realloc_fail += stack.resize(2 << 12);
    }
    setrlimit(RLIMIT_DATA, &rlim);

    if (!realloc_fail)
        return TEST_FAILED;

    return TEST_SUCCESSFUL;
}

inline int fail_with_msg(const char *msg){
    std::cout << msg;
    return TEST_FAILED;
}