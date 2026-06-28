#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_case.h"

int test_run_tests(const char *name, TestCase *tests, size_t count)
{
    printf("Running %s tests...\n", name);

    int status = 0;
    TestCaseOutput *output = malloc(sizeof(TestCaseOutput));
    for (size_t i = 0; i < count; i++) {
        tests[i].fn(output);
        if (output->count == 0) {
            printf("\t[PASS] %s\n", tests[i].name);
        } else {
            printf("\t[FAIL] %s\n", tests[i].name);

            for (int y = 0; y < output->count; y++) {
                printf("\t\t -> %s\n", output->messages[y]);
            }

            status = -1;
        }

        memset(output, 0, sizeof(&output));
        output->count = 0;
    }

    if (status == 0) {
        printf("[PASS] %s tests\n", name);
    } else {
        printf("[FAIL] %s tests\n", name);
    }

    return status;
}

void test_fail(TestCaseOutput *output, const char *message)
{
    if (strlen(message) > OUTPUT_MESSAGE_SIZE) {
        fprintf(stderr, "test_add_message: message to big");
    }

    strcpy(output->messages[output->count], message);
    output->count++;
}

void test_string_is_equal(TestCaseOutput *output, const char *expected, const char *actual)
{
    char message[OUTPUT_MESSAGE_SIZE] = { 0 };
    if (strcmp(expected, actual) != 0) {
        sprintf(message, "expected: %s, actual: %s", expected, actual);
        test_fail(output, message);
    }
}

void test_int_is_equal(TestCaseOutput *output, int expected, int actual)
{
    char message[OUTPUT_MESSAGE_SIZE] = { 0 };
    if (expected != actual) {
        sprintf(message, "expected: %d, actual: %d", expected, actual);
        test_fail(output, message);
    }
}

bool test_is_null(TestCaseOutput *output, const void *pointer, const char *message)
{
    if (pointer == NULL) {
        test_fail(output, message);
        return true;
    }

    return false;
}
