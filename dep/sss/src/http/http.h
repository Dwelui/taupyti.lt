#ifndef HTTP_H
#define HTTP_H

#include <ncurses.h>
#include <stdio.h>
#include "../route.h"

bool http_handle(int request_socketfd, const Routes *routes, const char *templates_directory, Response *response);

#endif // HTTP_H
