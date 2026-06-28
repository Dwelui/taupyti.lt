#include <stdio.h>
#include <string.h>

#include "test_case.h"

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
