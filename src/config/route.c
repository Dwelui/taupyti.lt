#include "route.h"

int get_routes(struct Route **routes, size_t *count)
{
    static struct Route temp[] = {
        {.name = "index", .path = "/"},
    };
    *routes = temp;

    size_t count_temp = sizeof(temp) / sizeof(temp[0]);
    *count = count_temp;

    return 0;
}
