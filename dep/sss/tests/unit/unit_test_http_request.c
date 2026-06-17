#include "unit_test_http_request.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../http_request.h"

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

char *test_http_request_parse_version()
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");

    HttpRequest request = http_request_create(input, sizeof(input));

    if (request.version != HTTP_VERSION_1_1) {
        return "request version does not match";
    }

    if (request.method != HTTP_METHOD_GET) {
        return "request method does not match";
    }

    if (strcmp(request.path, "/") != 0) {
        return "request path does not match";
    }

    return NULL;
}

char *test_http_request_parse_method()
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");

    HttpRequest request = http_request_create(input, sizeof(input));

    if (request.method != HTTP_METHOD_GET) {
        return "request method does not match";
    }

    return NULL;
}

char *test_http_request_parse_path()
{
    char *input = file_read("tests/fixtures/http/valid_get_2.http");

    HttpRequest request = http_request_create(input, sizeof(input));

    if (strcmp(request.path, "/a/very/long/request/path/index.html") != 0) {
        return "request path does not match";
    }

    return NULL;
}

char *test_http_request_parse_query_parameters()
{
    char *input = file_read("tests/fixtures/http/valid_get_queries_1.http");

    HttpRequest request = http_request_create(input, sizeof(input));

    const HttpQueryParameter *query_parameter;
    query_parameter = http_request_find_query_parameter_by_name(&request, "product_name");
    if (strcmp(query_parameter->value, "milk") != 0) {
        return "request query_parameter 'product_name' does not match 'milk'";
    }

    query_parameter = http_request_find_query_parameter_by_name(&request, "product_price");
    if (strcmp(query_parameter->value, "1.70") != 0) {
        return "request query_parameter 'product_price' does not match '1.70'";
    }

    query_parameter = http_request_find_query_parameter_by_name(&request, "product_count");
    if (strcmp(query_parameter->value, "2") != 0) {
        return "request query_parameter 'product_count' does not match '2'";
    }

    return NULL;
}
