#ifndef ROUTER_H
#define ROUTER_H

#include "../../dep/sss/src/http/request.h"
#include "../../dep/sss/src/http/response.h"

int route(const HttpRequest *req, HttpResponse *res);

#endif // ROUTER_H
