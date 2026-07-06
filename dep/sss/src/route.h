#ifndef ROUTE_H
#define ROUTE_H

#include "http/request.h"
#include "http/response.h"

typedef int (*RouteHandler)(const Request *req, Response *res);

typedef struct {
    HttpMethod method;
    char *path;
    RouteHandler handler;
} Route;

typedef struct {
    Route *items;
    size_t count;
} Routes;

int route_request(const Routes *routes, const Request *req, Response *res);

#endif // ROUTE_H
