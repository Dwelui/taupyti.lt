#include "router.h"
#include "../controller/default_controller.h"

int route(const HttpRequest *req)
{
    if (strcmp(req->path, "/") == 0) {
        return default_controller_index(req);
    }

    return 0;
}
