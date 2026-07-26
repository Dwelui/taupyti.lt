#ifndef RESPONSE_H
#define RESPONSE_H

#include "request.h"

typedef struct {
    HttpVersion protocol;
    int status_code;
    string reason_phrase;

    char *template_path;
} Response;

Response *response_create();
void response_free(Response *res);

string response_to_string(const Response *res);

#endif // RESPONSE_H
