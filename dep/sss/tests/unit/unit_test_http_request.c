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

char *test_http_request_create_parse_request_line_1()
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

char *test_http_request_create_parse_request_line_2()
{
    char *input = file_read("tests/fixtures/http/valid_get_2.http");

    HttpRequest request = http_request_create(input, sizeof(input));

    if (request.version != HTTP_VERSION_1_1) {
        return "request version does not match";
    }

    if (request.method != HTTP_METHOD_GET) {
        return "request method does not match";
    }

    if (strcmp(request.path, "/a/very/long/request/path/index.html") != 0) {
        return "request path does not match";
    }

    return NULL;
}

char *test_http_request_create_parse_request_line_3()
{
    char *input = file_read("tests/fixtures/http/valid_get_queries_1.http");

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
