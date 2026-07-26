#include "response.h"
#include "request.h"

#include <stdlib.h>

Response *response_create()
{
    Response *response = malloc(sizeof(Response));
    response->protocol = HTTP_VERSION_1_1;
    response->status_code = 200;
    response->reason_phrase = string_from_cstring("OK");

    return response;
}

void response_free(Response *res)
{
    free(res);
}

string response_to_string(const Response *res)
{
    string_array status_line = string_array_create(4);

    string protocol_version = request_version_to_string(res->protocol);
    string_array_push(status_line, protocol_version);

    string status_code = string_from_int(res->status_code);
    string_array_push(status_line, status_code);

    string reason_phrase = response_reason_phrase_to_string(res->reason_phrase);
    string_array_push(status_line, reason_phrase);

    string_array_push(status_line, string_empty()); // For additional \r\n.
    string result = string_join(status_line, "\r\n");

    return string_from_cstring("HTTP/1.1 200 OK\r\n\r\n");
}
