#include "route.h"
#include <string.h>

int route_request(const Routes *routes, const Request *req, Response *res)
{
    char *path = string_to_cstring(req->path);

    Route route;
    for (size_t i = 0; i < routes->count; i++) {
        route = routes->items[i];

        if (strcmp(route.path, path) != 0) {
            continue;
        }

        if (route.method != req->method) {
            continue;
        }

        route.handler(req, res);
        return 0;
    }

    return -1;
}
