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

void test_request_parse_query_parameters(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_queries_1.http");

    Request *request = request_create(input, sizeof(input));

    string query_value;
    query_value = request_find_query_value_by_name_cstring(request, "product_name");
    test_cstring_is_equal_to_string(output, "milk", query_value);

    query_value = request_find_query_value_by_name_cstring(request, "product_price");
    test_cstring_is_equal_to_string(output, "1.70", query_value);

    query_value = request_find_query_value_by_name_cstring(request, "product_count");
    test_cstring_is_equal_to_string(output, "2", query_value);

    free(input);
    request_free(request);
}
