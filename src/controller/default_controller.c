#include "default_controller.h"

int default_controller_index(const HttpRequest *req, HttpResponse *res)
{
    res->template_path = "index.html";

    return 0;
}

int default_controller_store(const HttpRequest *req, HttpResponse *res)
{
    res->template_path = "index.html";

    return 0;
}
