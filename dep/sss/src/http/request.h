#ifndef REQUEST_H
#define REQUEST_H

#include <curses.h>
#include "../../../string/src/string.h"

typedef enum {
    HTTP_VERSION_1_1,
} HttpVersion;

typedef enum {
    HTTP_METHOD_GET,
    HTTP_METHOD_PUT,
    HTTP_METHOD_POST,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_PATCH,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_TRACE,
} HttpMethod;

typedef struct {
    HttpVersion version;
    HttpMethod method;
    string query;
    string path;
    string url;
} HttpRequest;

HttpRequest *http_request_create(char *req_buf, size_t req_len);
void http_request_free(HttpRequest *req);

string *http_request_find_query_value_by_name_cstring(const HttpRequest *req, const char *name);
string *http_request_find_query_value_by_name(const HttpRequest *req, string name);

HttpMethod http_request_string_to_method(string method);
char *http_request_method_to_string(HttpMethod method);

HttpVersion http_request_string_to_version(string version);
char *http_request_version_to_string(HttpVersion version);

#endif // REQUEST_H
