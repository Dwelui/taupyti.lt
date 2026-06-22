#include "dep/sss/kernel.h"
#include "dep/sss/src/route.h"
#include "src/controller/default_controller.h"
#include <stdlib.h>

int main()
{
    Route route_items[] = {
        { .path = "/", .fn = default_controller_index},
    };

    Routes *routes = malloc(sizeof(Routes));
    routes->items = route_items;
    routes->count = sizeof(route_items) / sizeof(route_items[0]);

    boot(routes);
}
