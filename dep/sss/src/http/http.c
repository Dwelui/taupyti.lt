#include "request.h"
#include "response.h"
#include "http.h"

#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void print_formatted_request_line(const Request *req)
{
    printf(
        "[%s] %s %s %s\n",
        "2026-06-15 18:54:35",
        request_method_to_string(req->method),
        string_to_cstring(req->url),
        request_version_to_string(req->version)
    );
}

bool http_handle(int request_socketfd, const Routes *routes, const char *templates_directory)
{
    char req_msg[1024];
    ssize_t req_bytes_received = recv(request_socketfd, req_msg, sizeof(req_msg), 0);
    if (req_bytes_received == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    } else if (req_bytes_received == 0) {
        printf("recv: connection closed");
    }

    const Request *request = request_create(req_msg, sizeof(req_msg));
    print_formatted_request_line(request);

    // INFO: Extract request/response lifecycle into testable method.
    // You can pass request socket to it or other handler and send the response through tcp or testing env.
    Response *response = response_create();
    if (route_request(routes, request, response) != 0) {
        char *not_found_response = "HTTP/1.1 404 Not Found\r\n\r\n";
        ssize_t response_bytes_sent = send(request_socketfd, not_found_response, strlen(not_found_response), 0);
        (void)response_bytes_sent;

        printf("%s", not_found_response);

        close(request_socketfd);
        return false;
    }

    int len;
    char file_path[1024];
    len = snprintf(file_path, sizeof(file_path), "%s/%s", templates_directory, response->template_path);
    file_path[len] = '\0';

    int file_fd = open(file_path, O_RDONLY);
    if (file_fd == -1) {
        perror("file");
        exit(EXIT_FAILURE);
    }

    __off_t file_length = lseek(file_fd, 0, SEEK_END);
    lseek(file_fd, 0, SEEK_SET);

    char response_header[1024];
    len = snprintf(response_header, sizeof(response_header), "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\n", file_length);
    response_header[len] = '\0';
    printf("%s", response_header);
    ssize_t response_bytes_sent = send(request_socketfd, response_header, strlen(response_header), 0);
    if (response_bytes_sent == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    } else if (response_bytes_sent == 0) {
        printf("send: partial message sent");
    }

    size_t response_body_len = file_length * sizeof(char);
    char *response_body = malloc(response_body_len + 1);
    ssize_t file_len = read(file_fd, response_body, response_body_len);
    if (file_len == -1) {
        perror("read file");
        exit(EXIT_FAILURE);
    }
    response_body[file_len] = '\0';
    close(file_fd);

    response_bytes_sent = send(request_socketfd, response_body, strlen(response_body), 0);
    if (response_bytes_sent == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    } else if (response_bytes_sent == 0) {
        printf("send: partial message sent");
    }

    return true;
}
