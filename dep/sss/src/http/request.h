#ifndef REQUEST_H
#define REQUEST_H

#include <curses.h>
#include "../../../string/src/string.h"
#include "../variable.h"

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
    string raw;
    HttpVersion version;
    HttpMethod method;
    string query;
    string path;
    string url;
    string headers;
    string body;
} Request;

Request *request_create(char *req_buf, size_t req_len);
void request_free(Request *req);

variable *request_body_get(const Request *req, const char *name);

HttpMethod request_string_to_method(string method);
char *request_method_to_string(HttpMethod method);

HttpVersion request_string_to_version(string version);
char *request_version_to_string(HttpVersion version);

#endif // REQUEST_H
