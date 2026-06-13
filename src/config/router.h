#ifndef ROUTER_H
#define ROUTER_H

#include <string.h>
#include "../../dep/sss/http_request.h"
#include "../../dep/sss/http_response.h"

int route(const HttpRequest *req, HttpResponse *res);

#endif // ROUTER_H
