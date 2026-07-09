#include <fcntl.h>
#include <unistd.h>

#include "../../tests.h"
#include "../../../src/http/request.h"

void test_request_parse_version(TestCaseOutput *output)
{
    Request *request = requestFromFixturePath("tests/fixtures/http/valid_get_1.http");

    test_int_is_equal(output, HTTP_VERSION_1_1, request->version);

    request_free(request);
}

void test_request_parse_method(TestCaseOutput *output)
{
    Request *request = requestFromFixturePath("tests/fixtures/http/valid_get_1.http");

    test_int_is_equal(output, HTTP_METHOD_GET, request->method);

    request_free(request);
}

void test_request_parse_path(TestCaseOutput *output)
{
    Request *request = requestFromFixturePath("tests/fixtures/http/valid_get_2.http");

    test_cstring_is_equal_to_string(output, "/a/very/long/request/path/index.html", request->path);

    request_free(request);
}

void test_request_parse_path_2(TestCaseOutput *output)
{
    Request *request = requestFromFixturePath("tests/fixtures/http/valid_get_queries_1.http");

    test_cstring_is_equal_to_string(output, "/", request->path);

    request_free(request);
}
