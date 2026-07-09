#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../tests.h"
#include "../../../src/http/request.h"

void test_request_parse_version(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");
    Request *request = request_create(input, sizeof(input));

    test_int_is_equal(output, HTTP_VERSION_1_1, request->version);

    free(input);
    request_free(request);
}

void test_request_parse_method(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");
    Request *request = request_create(input, sizeof(input));

    test_int_is_equal(output, HTTP_METHOD_GET, request->method);

    free(input);
    request_free(request);
}

void test_request_parse_path(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_2.http");
    Request *request = request_create(input, sizeof(input));

    char *path = string_to_cstring(request->path);

    test_string_is_equal(output, "/a/very/long/request/path/index.html", path);

    free(input);
    free(path);
    request_free(request);
}

void test_request_parse_path_2(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_queries_1.http");
    Request *request = request_create(input, sizeof(input));

    char *path = string_to_cstring(request->path);

    test_string_is_equal(output, "/", path);

    free(input);
    free(path);
    request_free(request);
}
