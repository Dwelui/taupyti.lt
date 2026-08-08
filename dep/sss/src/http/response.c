#include "response.h"
#include "request.h"

#include <stdio.h>
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
    string_array status_line = string_array_create(3);

    string protocol_version = http_version_to_string(res->protocol);
    string_array_push(&status_line, protocol_version);

    string status_code = string_from_int(res->status_code);
    string_array_push(&status_line, status_code);

    string_array_push(&status_line, res->reason_phrase);

    string status_line_string = string_join(status_line, " ");
    string_array_free(status_line);
    string_free(&status_code);

    // TODO: refactor when string_append is implemented
    string_array result = string_array_create(2);
    string_array_push(&result, status_line_string);
    string_array_push(&result, string_empty());
    string result_string = string_join(result, "\r\n\r\n");
    string_free(&status_line_string);
    string_array_free(result);

    return result_string;
}
