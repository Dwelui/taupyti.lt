#include "../../src/string.h"
#include <stddef.h>
#include <string.h>
#include "test_string.h"

void test_string_from_cstring(TestCaseOutput *output)
{
    string_from_cstring("Hello World!");
}

void test_string_from_cstring_correct_count(TestCaseOutput *output)
{
    char *original = "Hello World!";

    string string = string_from_cstring(original);

    test_int_is_equal(output, 12, string.count);
}

void test_string_from_cstring_data_is_same_as_original(TestCaseOutput *output)
{
    char *original = "Hello World!";

    string string = string_from_cstring(original);

    for (size_t i = 0; i < strlen(original); i++) {
        if (original[i] != string.data[i]) {
            test_fail(output, "letters do not match");
        }
    }
}

void test_string_to_cstring(TestCaseOutput *output)
{
    string original = string_from_cstring("Hello World!");

    char *cstring = string_to_cstring(original);

    for (size_t i = 0; i < strlen(cstring); i++) {
        if (original.data[i] != cstring[i]) {
            test_fail(output, "letters do not match");
        }
    }
}
