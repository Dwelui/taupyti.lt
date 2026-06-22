#ifndef ROUTE_H
#define ROUTE_H

#include "http/request.h"
#include "http/response.h"

typedef int (*RouteHandler)(const HttpRequest *req, HttpResponse *res);

typedef struct {
    char path[1024];
    RouteHandler handler;
} Route;

typedef struct {
    Route *items;
    size_t count;
} Routes;

int route_request(const Routes *routes, const HttpRequest *req, HttpResponse *res);

#endif // ROUTE_H
