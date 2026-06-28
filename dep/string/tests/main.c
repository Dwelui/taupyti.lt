#include "../../test/src/test.h"
#include "../src/string.h"

#include <string.h>

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


void test_string_split(TestCaseOutput *output)
{
    string string = string_from_cstring("aa, bb, cc, dd, ee, ff");

    string_array string_array = string_split(string, ", ");
}

void test_string_split_starts_with_delimeter(TestCaseOutput *output)
{
    string string = string_from_cstring(", aa, bb, cc, dd, ee, ff");

    string_array string_array = string_split(string, ", ");
}

void test_string_split_starts_with_longer_delimeter(TestCaseOutput *output)
{
    string string = string_from_cstring(" , aa , bb , cc , dd , ee , ff");

    string_array string_array = string_split(string, " , ");
}

void test_string_split_ends_with_delimeter(TestCaseOutput *output)
{
    string string = string_from_cstring("aa, bb, cc, dd, ee, ff, ");

    string_array string_array = string_split(string, ", ");
}

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_string_from_cstring),
    TEST_CASE_REGISTER(test_string_from_cstring_correct_count),
    TEST_CASE_REGISTER(test_string_from_cstring_data_is_same_as_original),
    TEST_CASE_REGISTER(test_string_to_cstring),
    TEST_CASE_REGISTER(test_string_split),
    TEST_CASE_REGISTER(test_string_split_starts_with_delimeter),
    TEST_CASE_REGISTER(test_string_split_starts_with_longer_delimeter),
    TEST_CASE_REGISTER(test_string_split_ends_with_delimeter),
};


int main()
{
    test_run_tests("Unit", unit_tests, sizeof(unit_tests) / sizeof(unit_tests[0]));
}
