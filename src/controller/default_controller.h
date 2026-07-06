#ifndef DEFAULT_CONTROLLER_H
#define DEFAULT_CONTROLLER_H

#include "../../dep/sss/src/http/request.h"
#include "../../dep/sss/src/http/response.h"

int default_controller_index(const Request *req, Response *res);
int default_controller_store(const Request *req, Response *res);

#endif // DEFAULT_CONTROLLER_H
