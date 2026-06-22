#ifndef ROUTE_H
#define ROUTE_H

#include "http/request.h"
#include "http/response.h"

typedef struct {
    char path[1024];
    int (*fn)(const HttpRequest *req, HttpResponse *res);
} Route;

typedef struct {
    Route items[32];
    size_t count;
} Routes;

int route_request(const Routes *routes, const HttpRequest *req, HttpResponse *res);

#endif // ROUTE_H
