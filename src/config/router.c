#include <string.h>

#include "router.h"
#include "../controller/default_controller.h"

int route(const HttpRequest *req, HttpResponse *res)
{
    if (strcmp(req->path, "/") == 0) {
        return default_controller_index(req, res);
    } else {
        return -1;
    }

    return 0;
}
