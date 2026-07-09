#ifndef TESTS_H
#define TESTS_H

#include "../../test/src/test.h"
#include "../src/http/request.h"

Request *requestFromFixturePath(const char *path);

// ------------------------- UNIT --------------------------------

void test_request_parse_version(TestCaseOutput *output);
void test_request_parse_method(TestCaseOutput *output);
void test_request_parse_path(TestCaseOutput *output);
void test_request_parse_path_2(TestCaseOutput *output);

// ------------------------- INTEGRATION -------------------------

void test_request_get_variable_from_body(TestCaseOutput *output);

#endif // TESTS_H
