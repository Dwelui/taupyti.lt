#ifndef TEST_REQUEST_H
#define TEST_REQUEST_H

#include "../../../../test/src/test.h"

void test_request_parse_version(TestCaseOutput *output);
void test_request_parse_method(TestCaseOutput *output);
void test_request_parse_path(TestCaseOutput *output);
void test_request_parse_path_2(TestCaseOutput *output);
void test_request_parse_query_parameters(TestCaseOutput *output);

#endif // TEST_REQUEST_H
