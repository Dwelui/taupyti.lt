#include "../../test/src/test.h"
#include "unit/test_string.h"

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_string_from_cstring),
    TEST_CASE_REGISTER(test_string_from_cstring_correct_count),
    TEST_CASE_REGISTER(test_string_from_cstring_data_is_same_as_original),
    TEST_CASE_REGISTER(test_string_to_cstring),
};

int main()
{
    test_run_tests("Unit", unit_tests, sizeof(unit_tests) / sizeof(unit_tests[0]));
}
