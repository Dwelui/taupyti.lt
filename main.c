#include "dep/sss/kernel.h"
#include "dep/sss/src/http/request.h"
#include "dep/sss/src/route.h"
#include "src/controller/default_controller.h"
#include <stdlib.h>

int main()
{
    Route route_items[] = {
        { .method = HTTP_METHOD_GET, .path = "/", .handler = default_controller_index},
        { .method = HTTP_METHOD_POST, .path = "/", .handler = default_controller_store},
    };

    Routes *routes = malloc(sizeof(Routes));
    routes->items = route_items;
    routes->count = sizeof(route_items) / sizeof(route_items[0]);

    boot(routes);
}
