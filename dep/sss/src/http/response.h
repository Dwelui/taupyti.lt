#ifndef RESPONSE_H
#define RESPONSE_H

#include "request.h"

typedef struct {
    HttpVersion protocol;
    HttpMethod status_code;
    string reason_phrase;

    char *template_path;
} Response;

Response *response_create();

#endif // RESPONSE_H
