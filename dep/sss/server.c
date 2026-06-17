#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include "http_request.h"
#include "../../src/config/router.h"
#include "http_response.h"

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

    buf[last_slash_position] = '\0';

    return (ssize_t)last_slash_position;
}

void print_formatted_request_line(const HttpRequest *req, const struct addrinfo *req_addr)
{
    printf(
        "[%s] %s %s %s %s\n",
        "2026-06-15 18:54:35",
        http_request_method_to_string(req->method),
        req->path,
        http_request_version_to_string(req->version),
        "<ip address>"// req_addr.ai_addr->sa_data
    );
}

int main(void)
{
    char root_dir[1024];
    if (get_root_dir(root_dir, sizeof(root_dir)) != -1) {
        printf("Root directory: %s\n", root_dir);
    }

    char templates_dir[1024];
    int len = snprintf(templates_dir, sizeof(templates_dir), "%s/%s", root_dir, "src/templates");
    templates_dir[len] = '\0';
    printf("Templates directory: %s\n", templates_dir);

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
        int req_sockfd = accept(server_sockfd, (struct sockaddr *)&req_addr, &req_addr_size);
        if (req_sockfd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char req_msg[1024];
        ssize_t req_bytes_received = recv(req_sockfd, req_msg, sizeof(req_msg), 0);
        if (req_bytes_received == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        } else if (req_bytes_received == 0) {
            printf("recv: connection closed");
        }

        HttpRequest request = http_request_create(req_msg, sizeof(req_msg));
        print_formatted_request_line(&request, &req_addr);

        HttpResponse response;
        status = route(&request, &response);
        if (status < 0) {
            fprintf(stderr, "route: %s with error code: %d\n", request.path, status);
            exit(EXIT_FAILURE);
        }

        char file_path[1024];
        len = snprintf(file_path, sizeof(file_path), "%s/%s", templates_dir, response.template_path);
        file_path[len] = '\0';
        printf("File path: %s\n", file_path);

        int file_fd = open(file_path, O_RDONLY);
        if (file_fd == -1) {
            perror("file");
            exit(EXIT_FAILURE);
        }

        char file_buf[1024];
        ssize_t file_len = read(file_fd, file_buf, sizeof(file_buf));
        if (file_len == -1) {
            perror("read file");
            exit(EXIT_FAILURE);
        }
        file_buf[file_len] = '\0';
        close(file_fd);

        char res_msg[1024];
        len = snprintf(res_msg, sizeof(res_msg), "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\n%s", file_len, file_buf);
        res_msg[len] = '\0';
        ssize_t res_bytes_sent = send(req_sockfd, res_msg, strlen(res_msg), 0);
        if (res_bytes_sent == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        } else if (res_bytes_sent == 0) {
            printf("send: partial message sent");
        }

        close(req_sockfd);
    }

    close(server_sockfd);

    return 0;
}
