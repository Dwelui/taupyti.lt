#include "response.h"

#include <stdlib.h>

Response *response_create()
{
    Response *response = malloc(sizeof(Response));

    return response;
}

void response_free(Response *res)
{
    free(res);
}
