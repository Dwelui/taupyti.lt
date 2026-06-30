#include "../../test/src/test.h"
#include "unit/http/test_request.h"

TestCase unit_tests[] = {
    TEST_CASE_REGISTER(test_http_request_parse_version),
    TEST_CASE_REGISTER(test_http_request_parse_method),
    TEST_CASE_REGISTER(test_http_request_parse_path),
    TEST_CASE_REGISTER(test_http_request_parse_path_2),
    TEST_CASE_REGISTER(test_http_request_parse_query_parameters),
};

int main()
{
    test_run_tests("Unit", unit_tests, sizeof(unit_tests) / sizeof(unit_tests[0]));
}
