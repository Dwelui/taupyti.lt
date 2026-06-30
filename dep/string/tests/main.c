#include "../../test/src/test.h"
#include "../src/string.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void test_string_split_1(TestCaseOutput *output)
{
    string string = string_from_cstring("aa, bb, cc, dd, ee, ff");

    string_array string_array = string_split(string, ", ");
    test_string_is_equal(output, "aa", string_to_cstring(string_array.items[0]));
    test_string_is_equal(output, "bb", string_to_cstring(string_array.items[1]));
    test_string_is_equal(output, "cc", string_to_cstring(string_array.items[2]));
    test_string_is_equal(output, "dd", string_to_cstring(string_array.items[3]));
    test_string_is_equal(output, "ee", string_to_cstring(string_array.items[4]));
    test_string_is_equal(output, "ff", string_to_cstring(string_array.items[5]));
}

void test_string_split_2(TestCaseOutput *output)
{
    string string = string_from_cstring("GET / HTTP/1.1");

    string_array string_array = string_split(string, " ");
    test_string_is_equal(output, "GET", string_to_cstring(string_array.items[0]));
    test_string_is_equal(output, "/", string_to_cstring(string_array.items[1]));
    test_string_is_equal(output, "HTTP/1.1", string_to_cstring(string_array.items[2]));
}

void test_string_split_starts_with_delimeter(TestCaseOutput *output)
{
    string string = string_from_cstring(", aa, bb, cc, dd, ee, ff");

    string_array string_array = string_split(string, ", ");
    test_string_is_equal(output, "aa", string_to_cstring(string_array.items[0]));
    test_string_is_equal(output, "bb", string_to_cstring(string_array.items[1]));
    test_string_is_equal(output, "cc", string_to_cstring(string_array.items[2]));
    test_string_is_equal(output, "dd", string_to_cstring(string_array.items[3]));
    test_string_is_equal(output, "ee", string_to_cstring(string_array.items[4]));
    test_string_is_equal(output, "ff", string_to_cstring(string_array.items[5]));
}

void test_string_split_starts_with_longer_delimeter(TestCaseOutput *output)
{
    string string = string_from_cstring(" , aa , bb , cc , dd , ee , ff");

    string_array string_array = string_split(string, " , ");
    test_string_is_equal(output, "aa", string_to_cstring(string_array.items[0]));
    test_string_is_equal(output, "bb", string_to_cstring(string_array.items[1]));
    test_string_is_equal(output, "cc", string_to_cstring(string_array.items[2]));
    test_string_is_equal(output, "dd", string_to_cstring(string_array.items[3]));
    test_string_is_equal(output, "ee", string_to_cstring(string_array.items[4]));
    test_string_is_equal(output, "ff", string_to_cstring(string_array.items[5]));
}

void test_string_split_ends_with_delimeter(TestCaseOutput *output)
{
    string string = string_from_cstring("aa, bb, cc, dd, ee, ff, ");

    string_array string_array = string_split(string, ", ");
    test_string_is_equal(output, "aa", string_to_cstring(string_array.items[0]));
    test_string_is_equal(output, "bb", string_to_cstring(string_array.items[1]));
    test_string_is_equal(output, "cc", string_to_cstring(string_array.items[2]));
    test_string_is_equal(output, "dd", string_to_cstring(string_array.items[3]));
    test_string_is_equal(output, "ee", string_to_cstring(string_array.items[4]));
    test_string_is_equal(output, "ff", string_to_cstring(string_array.items[5]));
}

void test_string_starts_at_returns_0_with_same_string(TestCaseOutput *output)
{
    string target = string_from_cstring("Hello");
    string substring = string_from_cstring("Hello");

    size_t position = string_starts_at(target, substring);
    test_int_is_equal(output, 0, (int)position);
}

void test_string_starts_at_returns_correct_position(TestCaseOutput *output)
{
    string target = string_from_cstring("Hello");
    string substring = string_from_cstring("llo");

    size_t position = string_starts_at(target, substring);
    test_int_is_equal(output, 2, (int)position);
}

void test_string_starts_at_returns_error_on_miss(TestCaseOutput *output)
{
    string target = string_from_cstring("Hello");
    string substring = string_from_cstring("World!");

    size_t position = string_starts_at(target, substring);
    test_int_is_equal(output, -1, (int)position);
}

void test_string_starts_at_returns_error_on_substring_being_longer_than_target(TestCaseOutput *output)
{
    string target = string_from_cstring("Hello");
    string substring = string_from_cstring("Hello World!");

    size_t position = string_starts_at(target, substring);
    test_int_is_equal(output, -1, (int)position);
}

void test_string_starts_at_returns_correct_position_with_substr_from_data(TestCaseOutput *output)
{
    string target = string_from_cstring("Hello");

    size_t substr_len = 3;
    char *substr_data = malloc(sizeof(char) * substr_len);
    memcpy(substr_data, "llo", substr_len);
    string substring = string_from_data(substr_data, substr_len);

    size_t position = string_starts_at(target, substring);
    test_int_is_equal(output, 2, (int)position);
}

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_string_from_cstring_correct_count),
    TEST_CASE_REGISTER(test_string_from_cstring_data_is_same_as_original),
    TEST_CASE_REGISTER(test_string_to_cstring),
    TEST_CASE_REGISTER(test_string_split_1),
    TEST_CASE_REGISTER(test_string_split_2),
    TEST_CASE_REGISTER(test_string_split_starts_with_delimeter),
    TEST_CASE_REGISTER(test_string_split_starts_with_longer_delimeter),
    TEST_CASE_REGISTER(test_string_split_ends_with_delimeter),
    TEST_CASE_REGISTER(test_string_starts_at_returns_0_with_same_string),
    TEST_CASE_REGISTER(test_string_starts_at_returns_correct_position),
    TEST_CASE_REGISTER(test_string_starts_at_returns_error_on_miss),
    TEST_CASE_REGISTER(test_string_starts_at_returns_error_on_substring_being_longer_than_target),
    TEST_CASE_REGISTER(test_string_starts_at_returns_correct_position_with_substr_from_data),
};


int main()
{
    test_run_tests("Unit", unit_tests, sizeof(unit_tests) / sizeof(unit_tests[0]));
}
