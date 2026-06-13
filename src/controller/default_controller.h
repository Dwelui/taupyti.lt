#ifndef DEFAULT_CONTROLLER_H
#define DEFAULT_CONTROLLER_H

#include <stddef.h>
#include <stdio.h>
#include "../../dep/sss/http_request.h"
#include "../../dep/sss/http_response.h"

int default_controller_index(const HttpRequest *req, HttpResponse *res);

#endif // DEFAULT_CONTROLLER_H
