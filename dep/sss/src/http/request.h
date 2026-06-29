#ifndef REQUEST_H
#define REQUEST_H

#include <curses.h>

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
    char key[16];
    char value[64];
} HttpQueryParameter;

typedef struct {
    HttpQueryParameter items[32];
    size_t count;
} HttpQueryParameters;

typedef struct {
    HttpVersion version;
    HttpMethod method;
    HttpQueryParameters parameters;
    char path[1024];
    char url[1024];
} HttpRequest;

HttpRequest *http_request_create(char *req_buf, size_t req_len);
void http_request_free(HttpRequest *req);

const HttpQueryParameter *http_request_find_query_parameter_by_name(const HttpRequest *req, char *name);

HttpMethod http_request_string_to_method(const char *buf);
char *http_request_method_to_string(HttpMethod method);

HttpVersion http_request_string_to_version(const char *buf);
char *http_request_version_to_string(HttpVersion version);

#endif // REQUEST_H
