#include "request.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const HttpRequest *http_request_create(char *req_buf, size_t req_len)
{
    char method[8], url[1024], version[9];
    int matched = sscanf(req_buf, "%7s %1023s %8s", method, url, version);
    assert(matched == 3);

    HttpRequest *request = malloc(sizeof(HttpRequest));
    request->method = http_request_string_to_method(method);
    request->version = http_request_string_to_version(version);

    int query_start = 0;
    for (int i = 0; i < strlen(url); i++) {
        if (url[i] == '?') {
            query_start = i;
            break;
        }
    }

    char query[1024] = { 0 };
    if (query_start == 0) {
        strcpy(request->path, url);
    } else {
        strncpy(request->path, url, query_start);
        request->path[query_start] = '\0';
        strncpy(query, url + query_start + 1, strlen(url) - query_start);
        query[strlen(url) - query_start] = '\0';
    }

    int parameter_index = 0, y = 0;
    bool is_reading_key = true;
    for (int i = 0; i < strlen(query); i++) {
        if (is_reading_key) {
            request->parameters.items[parameter_index].key[y] = query[i];
        } else {
            request->parameters.items[parameter_index].value[y] = query[i];
        }
        y++;

        if (query[i + 1] == '=') {
            request->parameters.items[parameter_index].key[y] = '\0';
            y = 0;

            is_reading_key = false;
            i++;
            continue;
        }

        if (query[i + 1] == '&' || query[i + 1] == '\0') {
            request->parameters.items[parameter_index].value[y] = '\0';
            y = 0;

            parameter_index++;

            is_reading_key = true;
            i++;
            continue;
        }
    }
    request->parameters.count = parameter_index;

    return request;
}

const HttpQueryParameter *http_request_find_query_parameter_by_name(const HttpRequest *req, char *name)
{
    for (int i = 0; i < req->parameters.count; i++) {
        if (strcmp(req->parameters.items[i].key, name) == 0) {
            return &req->parameters.items[i];
        }
    }

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
