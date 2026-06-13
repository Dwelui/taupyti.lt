#include "default_controller.h"

int default_controller_index(const HttpRequest *req, HttpResponse *res)
{
    res->template_path = "index.html";

    return 0;
}
