#ifndef TEST_CASE_H
#define TEST_CASE_H

#define TEST_CASE_REGISTER(fn) { #fn, fn }

#include <stddef.h>

typedef struct {
    char messages[32][64];
    size_t count;
} TestCaseOutput;

typedef struct {
    const char *name;
    void (*fn)(TestCaseOutput *output);
} TestCase;

#endif // TEST_CASE_H
