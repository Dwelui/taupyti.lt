#include "request.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HttpRequest *http_request_create(char *req_buf, size_t req_len)
{
    (void)req_len;

    string_array request_rows = string_split(string_from_cstring(req_buf), "\n");

    string_array request_line_components = string_split(request_rows.items[0], " ");
    string_array_free(request_rows);

    HttpRequest *request = malloc(sizeof(HttpRequest));
    request->method = http_request_string_to_method(request_line_components.items[0]);
    request->url = request_line_components.items[1];
    request->version = http_request_string_to_version(request_line_components.items[2]);
    string_array_free(request_line_components);

    string_array path_and_query = string_split(request->url, "?");
    request->path = path_and_query.items[0];
    if (path_and_query.count == 2) {
        request->query = path_and_query.items[1];
    } else {
        request->query = string_from_cstring("");
    }
    string_array_free(path_and_query);

    return request;
}

void http_request_free(HttpRequest *req)
{
    free(req);
}

string http_request_find_query_value_by_name_cstring(const HttpRequest *req, const char *name)
{
    string name_string = string_from_cstring((char *)name);

    return http_request_find_query_value_by_name(req, name_string);
}

string http_request_find_query_value_by_name(const HttpRequest *req, string name)
{
    string result = string_empty();

    if (req->query.count == 0) {
        return result;
    }

    string_array parameters = string_split(req->query, "&");
    string_array key_and_value;
    for (size_t i = 0; i < parameters.count; i++) {
        key_and_value = string_split(parameters.items[i], "=");
        if (
            key_and_value.count == 2 &&
            string_is_equal(key_and_value.items[0], name)
        ) {
            result = key_and_value.items[1];
            break;
        }

        string_array_free(key_and_value);
    }

    string_array_free(key_and_value);
    string_array_free(parameters);

    return result;
}

HttpMethod http_request_string_to_method(string method)
{
    char *method_cstring = string_to_cstring(method);

    HttpMethod result;
    if (strcmp(method_cstring, "GET") == 0) {
        result = HTTP_METHOD_GET;
    } else if (strcmp(method_cstring, "PUT") == 0) {
        result = HTTP_METHOD_PUT;
    } else if (strcmp(method_cstring, "POST") == 0) {
        result = HTTP_METHOD_POST;
    } else if (strcmp(method_cstring, "DELETE") == 0) {
        result = HTTP_METHOD_DELETE;
    } else if (strcmp(method_cstring, "PATCH") == 0) {
        result = HTTP_METHOD_PATCH;
    } else if (strcmp(method_cstring, "HEAD") == 0) {
        result = HTTP_METHOD_HEAD;
    } else if (strcmp(method_cstring, "OPTIONS") == 0) {
        result = HTTP_METHOD_OPTIONS;
    } else if (strcmp(method_cstring, "TRACE") == 0) {
        result =HTTP_METHOD_TRACE;
    } else {
        assert(false);
    }

    free(method_cstring);

    return result;
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

HttpVersion http_request_string_to_version(string version)
{
    char *version_cstring = string_to_cstring(version);

    HttpVersion result;
    if (strcmp(version_cstring, "HTTP/1.1") == 0) {
        result = HTTP_VERSION_1_1;
    } else {
        assert(false);
    }

    free(version_cstring);

    return result;
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
