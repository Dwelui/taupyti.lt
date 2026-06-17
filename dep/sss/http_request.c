#include "http_request.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

HttpRequest http_request_create(char *req_buf, size_t req_len)
{
    char method[8], path[1024], version[9];
    int matched = sscanf(req_buf, "%7s %1023s %8s", method, path, version);
    assert(matched == 3);

    HttpRequest request;
    request.method = http_request_string_to_method(method);
    request.version = http_request_string_to_version(version);
    strcpy(request.path, path);

    return request;
}

const HttpQueryParameter *http_request_find_query_parameter_by_name(const HttpRequest *req, char *name)
{
    return NULL;
}

HttpMethod http_request_string_to_method(char *buf)
{
    if (strcmp(buf, "GET") == 0) {
        return HTTP_METHOD_GET;
    } else if (strcmp(buf, "PUT") == 0) {
        return HTTP_METHOD_PUT;
    } else if (strcmp(buf, "POST") == 0) {
        return HTTP_METHOD_POST;
    } else if (strcmp(buf, "DELETE") == 0) {
        return HTTP_METHOD_DELETE;
    } else if (strcmp(buf, "PATCH") == 0) {
        return HTTP_METHOD_PATCH;
    } else if (strcmp(buf, "HEAD") == 0) {
        return HTTP_METHOD_HEAD;
    } else if (strcmp(buf, "OPTIONS") == 0) {
        return HTTP_METHOD_OPTIONS;
    } else if (strcmp(buf, "TRACE") == 0) {
        return HTTP_METHOD_TRACE;
    } else {
        assert(false);
    }
}

char *http_request_method_to_string(HttpMethod method)
{
    switch (method) {
        case HTTP_METHOD_GET:
            return "GET";
        case HTTP_METHOD_PUT:
            return "PUT";
        case HTTP_METHOD_POST:
            return "POST";
        case HTTP_METHOD_DELETE:
            return "DELETE";
        case HTTP_METHOD_PATCH:
            return "PATCH";
        case HTTP_METHOD_HEAD:
            return "HEAD";
        case HTTP_METHOD_OPTIONS:
            return "OPTIONS";
        case HTTP_METHOD_TRACE:
            return "TRACE";
        default:
            assert(false);
    }
}

HttpVersion http_request_string_to_version(char *buf)
{
    if (strcmp(buf, "HTTP/1.1") == 0) {
        return HTTP_VERSION_1_1;
    } else {
        assert(false);
    }
}

char *http_request_version_to_string(HttpVersion version)
{
    switch (version) {
        case HTTP_VERSION_1_1:
            return "HTTP/1.1";
        default:
            assert(false);
    }
}
