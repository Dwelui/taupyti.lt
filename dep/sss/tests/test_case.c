#include "test_case.h"
#include <stdio.h>
#include <string.h>

void test_fail(TestCaseOutput *output, const char *message)
{
    if (strlen(message) > OUTPUT_MESSAGE_SIZE) {
        fprintf(stderr, "test_add_message: message to big");
    }

    strcpy(output->messages[output->count], message);
    output->count++;
}

bool test_is_null(TestCaseOutput *output, const void *pointer, const char *message)
{
    if (pointer == NULL) {
        test_fail(output, message);
        return true;
    }

    return false;
}

void test_string_is_equal(TestCaseOutput *output, const char *expected, const char *actual)
{
    char message[OUTPUT_MESSAGE_SIZE] = { 0 };
    if (strcmp(expected, actual) != 0) {
        sprintf(message, "expected: %s, actual: %s", expected, actual);
        test_fail(output, message);
    }
}
