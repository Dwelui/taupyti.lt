#include "../../test/src/test.h"
#include "unit/test_string.h"

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_string_create_from_cstring),
};

int main()
{
    test_run_tests("Unit", unit_tests, sizeof(unit_tests) / sizeof(unit_tests[0]));
}
