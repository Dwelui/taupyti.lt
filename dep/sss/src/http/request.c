#include "request.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Request *request_create(char *req_buf, size_t req_len)
{
    (void)req_len;

    size_t requestBufferLength = strlen(req_buf);
    char *requestBufferClone = malloc(requestBufferLength + 1);
    memset(requestBufferClone, 0, requestBufferLength + 1);
    memcpy(requestBufferClone, req_buf, requestBufferLength);

    Request *request = malloc(sizeof(Request));
    request->raw = string_from_cstring(requestBufferClone);

    string_array request_rows = string_split(request->raw, "\n");
    for (size_t i = 0; i < request_rows.count; i++) {
        string_trim(&request_rows.items[i]);
    }

    string_array request_line_components = string_split(request_rows.items[0], " ");
    string_array_free(request_rows);

    request->method = request_string_to_method(request_line_components.items[0]);
    request->url = request_line_components.items[1];
    request->version = request_string_to_version(request_line_components.items[2]);
    string_array_free(request_line_components);

    string_array path_and_query = string_split(request->url, "?");
    request->path = path_and_query.items[0];
    if (path_and_query.count == 2) {
        request->query = path_and_query.items[1];
    } else {
        request->query = string_from_cstring("");
    }
    string_array_free(path_and_query);

    ssize_t requestLineEndPosition = string_starts_at(request->raw, string_from_cstring("\r\n"));
    if (requestLineEndPosition == -1) {
        requestLineEndPosition = string_starts_at(request->raw, string_from_cstring("\n"));
    }
    size_t headerStartPosition = requestLineEndPosition + 1;

    ssize_t headerEndPosition = string_starts_at(request->raw, string_from_cstring("\r\n\r\n"));
    if (headerEndPosition == -1) {
        headerEndPosition = string_starts_at(request->raw, string_from_cstring("\n\n"));
    }

    size_t bodyStartPosition = headerEndPosition + 1;

    request->headers = string_substring(request->raw, headerStartPosition, headerEndPosition);
    string_trim(&request->headers);

    size_t bodyEndPosition = request->raw.count;
    if (bodyEndPosition - bodyStartPosition <= 4) {
        request->body = string_empty();
    } else {
        request->body = string_substring(request->raw, bodyStartPosition, request->raw.count);
        string_trim(&request->body);
    }

    return request;
}

void request_free(Request *req)
{
    free(req->raw.data);
    free(req);
}

Variable *request_body_get(const Request *req, const char *name)
{
    Variable *result = NULL;

    string_array variableKeyAndValueMap = string_split(req->body, "&");
    string_array keyAndValue;
    for (size_t i = 0; i < variableKeyAndValueMap.count; i++) {
        keyAndValue = string_split(variableKeyAndValueMap.items[i], "=");
        if (string_is_equal_cstring(keyAndValue.items[0], name)) {
            result = malloc(sizeof(Variable));
            result->raw = keyAndValue.items[1];
            string_array_free(keyAndValue);
            break;
        }
    }

    string_array_free(variableKeyAndValueMap);

    return result;
}

HttpMethod request_string_to_method(string method)
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
        result = HTTP_METHOD_TRACE;
    } else {
        assert(false);
    }

    free(method_cstring);

    return result;
}

char *request_method_to_string(HttpMethod method)
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

HttpVersion request_string_to_version(string version)
{
    HttpVersion result;
    if (string_is_equal_cstring(version, "HTTP/1.1")) {
        result = HTTP_VERSION_1_1;
    } else {
        assert(false);
    }

    return result;
}

char *request_version_to_string(HttpVersion version)
{
    switch (version) {
        case HTTP_VERSION_1_1:
            return "HTTP/1.1";
        default:
            assert(false);
    }
}
