#include "default_controller.h"

int default_controller_index(const Request *req, HttpResponse *res)
{
    res->template_path = "index.html";

    return 0;
}

int default_controller_store(const Request *req, HttpResponse *res)
{
    res->template_path = "index.html";

    return 0;
}
