#ifndef ROUTE_H
#define ROUTE_H

#include <stddef.h>
#include <stdio.h>

struct Route {
    char name[1024];
    char path[1024];
};

int get_routes(struct Route **routes, size_t *count);

#endif // ROUTE_H
