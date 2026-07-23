#include "response.h"

#include <stdlib.h>

Response *response_create()
{
    Response *response = malloc(sizeof(Response));

    return response;
}
