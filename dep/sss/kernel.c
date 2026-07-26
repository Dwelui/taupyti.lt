#include <iso646.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

#include "kernel.h"
#include "src/http/http.h"

#define PORT "3490" // the port server is listening to
#define BACKLOG 10 // how many pending connections queue holds

ssize_t get_root_dir(char* buf, size_t len)
{
    ssize_t result = readlink("/proc/self/exe", buf, len - 1);
    if (result == -1) {
        return -1;
    }

    buf[result] = '\0';

    size_t last_slash_position = 0;
    for (size_t i = 0; i < (size_t)result; i++) {
        if (buf[i] == '/') {
            last_slash_position = i;
        }
    }

    last_slash_position -= 6; // to remove 'build' directory

    buf[last_slash_position] = '\0';

    return (ssize_t)last_slash_position;
}

int boot(const Routes *routes)
{
    char root_dir[1024];
    if (get_root_dir(root_dir, sizeof(root_dir)) != -1) {
        printf("Root directory: %s\n", root_dir);
    }

    char templates_directory[1024];
    int len = snprintf(templates_directory, sizeof(templates_directory), "%s/%s", root_dir, "src/templates");
    templates_directory[len] = '\0';
    printf("Templates directory: %s\n", templates_directory);

    printf("\n");

    int status;

    struct addrinfo hints = {0};
    hints.ai_family = AF_INET; // USE IPv4
    hints.ai_socktype = SOCK_STREAM; // USE safe and reliable connection which by default is TCP
    hints.ai_flags = AI_PASSIVE; // Fill in my ip

    struct addrinfo *server_addr_result;
    status = getaddrinfo(NULL, PORT, &hints, &server_addr_result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    struct addrinfo *server_addr;
    int server_sockfd;
    for (server_addr = server_addr_result; server_addr != NULL; server_addr = server_addr_result->ai_next)
    {
        server_sockfd = socket(server_addr->ai_family, server_addr->ai_socktype, server_addr->ai_protocol);
        if (status == -1) {
            continue;
        }

        if (bind(server_sockfd, server_addr_result->ai_addr, server_addr_result->ai_addrlen) == 0) {
            break;
        }

        close(server_sockfd);
    }

    freeaddrinfo(server_addr_result);

    if (server_addr == NULL) {
        fprintf(stderr, "Failed to bind\n");
        exit(EXIT_FAILURE);
    }

    status = listen(server_sockfd, BACKLOG);
    if (status == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct addrinfo req_addr;
        socklen_t req_addr_size = sizeof(req_addr);
        int request_socketfd = accept(server_sockfd, (struct sockaddr *)&req_addr, &req_addr_size);
        if (request_socketfd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        http_handle(request_socketfd, routes, templates_directory);

        close(request_socketfd);
    }

    close(server_sockfd);

    return 0;
}
