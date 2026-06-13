#ifndef ROUTER_H
#define ROUTER_H

#include "../../dep/sss/http_request.h"
#include <string.h>

int route(const HttpRequest *req);

#endif // ROUTER_H
