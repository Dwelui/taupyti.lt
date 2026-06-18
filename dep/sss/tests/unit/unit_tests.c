#include "../test_case.h"
#include "unit_tests.h"
#include "unit_test_http_request.h"
#include <stdio.h>

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_http_request_parse_version),
    TEST_CASE_REGISTER(test_http_request_parse_method),
    TEST_CASE_REGISTER(test_http_request_parse_path),
    TEST_CASE_REGISTER(test_http_request_parse_path_2),
    TEST_CASE_REGISTER(test_http_request_parse_query_parameters),
};

// INFO: Might want to pass "char **output" to tests
// - Each test check fail concats to the output that is returned
// - Ouput is formatted and displayed and cleared for other test case.
// - Small utility functions for checking and formating output messages using templates
int run_unit_tests()
{
    int status = 0;
    char *test_output = NULL;

    for (int i = 0; i < sizeof(unit_tests) / sizeof(unit_tests[0]); i++) {
        test_output = unit_tests[i].fn();
        if (test_output == NULL) {
            printf("\t[PASS] %s\n", unit_tests[i].name);
        } else {
            printf("\t[FAIL] %s\n", unit_tests[i].name);
            printf("\t\t -> %s\n", test_output);
            status = -1;
        }
    }

    return status;
}
