#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../test_case.h"
#include "unit_tests.h"
#include "http/test_request.h"

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_http_request_parse_version),
    TEST_CASE_REGISTER(test_http_request_parse_method),
    TEST_CASE_REGISTER(test_http_request_parse_path),
    TEST_CASE_REGISTER(test_http_request_parse_path_2),
    TEST_CASE_REGISTER(test_http_request_parse_query_parameters),
};

int run_unit_tests()
{
    int status = 0;
    TestCaseOutput *output = malloc(sizeof(TestCaseOutput));
    for (int i = 0; i < sizeof(unit_tests) / sizeof(unit_tests[0]); i++) {
        unit_tests[i].fn(output);
        if (output->count == 0) {
            printf("\t[PASS] %s\n", unit_tests[i].name);
        } else {
            printf("\t[FAIL] %s\n", unit_tests[i].name);

            for (int y = 0; y < output->count; y++) {
                printf("\t\t -> %s\n", output->messages[y]);
            }

            status = -1;
        }

        memset(output, 0, sizeof(&output));
        output->count = 0;
    }

    return status;
}
