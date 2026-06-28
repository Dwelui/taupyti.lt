#ifndef TEST_H
#define TEST_H

#define TEST_CASE_REGISTER(fn) { #fn, fn }
#define OUTPUT_MESSAGE_SIZE 1024

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char messages[32][OUTPUT_MESSAGE_SIZE];
    size_t count;
} TestCaseOutput;

typedef struct {
    const char *name;
    void (*fn)(TestCaseOutput *output);
} TestCase;

int test_run_tests(const char *name, TestCase *tests, size_t count);

void test_fail(TestCaseOutput *output, const char *message);
void test_string_is_equal(TestCaseOutput *output, const char *expected, const char *actual);
void test_int_is_equal(TestCaseOutput *output, int expected, int actual);
bool test_is_null(TestCaseOutput *output, const void *pointer, const char *message);

#endif // TEST_H
