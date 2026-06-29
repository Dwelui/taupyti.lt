#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "test_request.h"
#include "../../../src/http/request.h"

char *file_read(const char *path)
{
    int file_fd = open(path, O_RDONLY);
    if (file_fd == -1) {
        perror("file_read open");
        return NULL;
    }

    size_t buf_len = 1024;
    char *buf = malloc(buf_len * sizeof(char));
    ssize_t bytes_read = read(file_fd, buf, buf_len - 1);
    if (bytes_read == -1) {
        perror("file_read read");
        return NULL;
    }

    buf[bytes_read] = '\0';

    close(file_fd);

    return buf;
}

void test_http_request_parse_version(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");

    HttpRequest *request = http_request_create(input, sizeof(input));

    test_int_is_equal(output, HTTP_VERSION_1_1, request->version);

    free(input);
    http_request_free(request);
}

void test_http_request_parse_method(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");

    HttpRequest *request = http_request_create(input, sizeof(input));

    test_int_is_equal(output, HTTP_METHOD_GET, request->method);

    free(input);
    http_request_free(request);
}

void test_http_request_parse_path(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_2.http");

    HttpRequest *request = http_request_create(input, sizeof(input));

    test_string_is_equal(output, "/a/very/long/request/path/index.html", request->path);

    free(input);
    http_request_free(request);
}

void test_http_request_parse_path_2(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_queries_1.http");

    HttpRequest *request = http_request_create(input, sizeof(input));

    test_string_is_equal(output, "/", request->path);

    free(input);
    http_request_free(request);
}

void test_http_request_parse_query_parameters(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_queries_1.http");

    HttpRequest *request = http_request_create(input, sizeof(input));

    const HttpQueryParameter *query_parameter;
    query_parameter = http_request_find_query_parameter_by_name(request, "product_name");
    if (test_is_null(output, query_parameter, "'product_name' not found")) return;
    test_string_is_equal(output, "milk", query_parameter->value);

    query_parameter = http_request_find_query_parameter_by_name(request, "product_price");
    if (test_is_null(output, query_parameter, "'product_price' not found")) return;
    test_string_is_equal(output, "1.70", query_parameter->value);

    query_parameter = http_request_find_query_parameter_by_name(request, "product_count");
    if (test_is_null(output, query_parameter, "'product_count' not found")) return;
    test_string_is_equal(output, "2", query_parameter->value);

    free(input);
    http_request_free(request);
}
