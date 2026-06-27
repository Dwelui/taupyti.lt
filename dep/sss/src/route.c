#include "route.h"
#include <string.h>

int route_request(const Routes *routes, const HttpRequest *req, HttpResponse *res)
{
    Route route;
    for (size_t i = 0; i < routes->count; i++) {
        route = routes->items[i];

        if (strcmp(route.path, req->path) != 0) {
            continue;
        }

        if (route.method != req->method) {
            continue;
        }

        route.handler(req, res);
    }

    return 0;
}
