#include "route.h"

static struct Route __routes[] = {
    {.name = "index", .path = "/"},
};

int get_routes(struct Route **routes, size_t *count)
{
    *routes = __routes;

    size_t count_temp = sizeof(__routes) / sizeof(__routes[0]);
    *count = count_temp;

    return 0;
}
