#include "unit_test_http_request.h"
#include <stdio.h>
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

void test_http_request_parse_version(TestCaseOutput *output)
{
    char *input = file_read("dep/sss/tests/fixtures/http/valid_get_1.http");

    const HttpRequest *request = http_request_create(input, sizeof(input));

    if (request->version != HTTP_VERSION_1_1) {
        sprintf(output->messages[output->count], "request version does not match");
        output->count++;
    }
}

void test_http_request_parse_method(TestCaseOutput *output)
{
    char *input = file_read("dep/sss/tests/fixtures/http/valid_get_1.http");

    const HttpRequest *request = http_request_create(input, sizeof(input));

    if (request->method != HTTP_METHOD_GET) {
        sprintf(output->messages[output->count], "request method does not match");
        output->count++;
    }
}

void test_http_request_parse_path(TestCaseOutput *output)
{
    char *input = file_read("dep/sss/tests/fixtures/http/valid_get_2.http");

    const HttpRequest *request = http_request_create(input, sizeof(input));

    if (strcmp(request->path, "/a/very/long/request/path/index.html") != 0) {
        sprintf(output->messages[output->count], "request path does not match");
        output->count++;
    }
}

void test_http_request_parse_path_2(TestCaseOutput *output)
{
    char *input = file_read("dep/sss/tests/fixtures/http/valid_get_queries_1.http");

    const HttpRequest *request = http_request_create(input, sizeof(input));

    if (strcmp(request->path, "/") != 0) {
        sprintf(output->messages[output->count], "request path does not match");
        output->count++;
    }
}

void test_http_request_parse_query_parameters(TestCaseOutput *output)
{
    char *input = file_read("dep/sss/tests/fixtures/http/valid_get_queries_1.http");

    const HttpRequest *request = http_request_create(input, sizeof(input));

    const HttpQueryParameter *query_parameter;
    query_parameter = http_request_find_query_parameter_by_name(request, "product_name");
    if (query_parameter == NULL) {
        sprintf(output->messages[output->count], "request query parameter 'product_name' not found");
        output->count++;
    } else if (strcmp(query_parameter->value, "milk") != 0) {
        sprintf(output->messages[output->count], "request query parameter 'product_name' expected 'milk' got '%s'", query_parameter->value);
        output->count++;
    }

    query_parameter = http_request_find_query_parameter_by_name(request, "product_price");
    if (query_parameter == NULL) {
        sprintf(output->messages[output->count], "request query parameter 'product_price' not found");
        output->count++;
    } else if (strcmp(query_parameter->value, "1.70") != 0) {
        sprintf(output->messages[output->count], "request query parameter 'product_price' expected '1.70' got '%s'", query_parameter->value);
        output->count++;
    }

    query_parameter = http_request_find_query_parameter_by_name(request, "product_count");
    if (query_parameter == NULL) {
        sprintf(output->messages[output->count], "request query parameter 'product_count' not found");
        output->count++;
    } else if (strcmp(query_parameter->value, "2") != 0) {
        sprintf(output->messages[output->count], "request query parameter 'product_count' expected '2' got '%s'", query_parameter->value);
        output->count++;
    }
}
