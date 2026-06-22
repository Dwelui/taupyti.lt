#include "route.h"
#include <string.h>

int route_request(const Routes *routes, const HttpRequest *req, HttpResponse *res)
{
    for (size_t i = 0; i < routes->count; i++) {
        if (strcmp(routes->items[i].path, req->path) == 0) {
            routes->items[i].handler(req, res);
        }
    }

    return 0;
}
