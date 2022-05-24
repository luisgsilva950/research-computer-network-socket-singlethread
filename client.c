#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include "common.c"

int main(int argc, char *argv[]) {
    if (argc < 3) print_client_usage_pattern();
    struct socket_context context = initialize_client_socket(argv[1], argv[2]);
    int _socket = context.socket;
    char *message = "remove sensor 01 04 in 2";
    int message_size = strlen(message) + 1;
    printf("Sending message: %s! \n", message);
    const int count = send(_socket, message, (ssize_t) message_size, 0);
    if (count != message_size) error("Error sending message");
    char buffer[BUFFER_SIZE_IN_BYTES];
    unsigned total_bytes_received = 0;
    while (1) {
        int bytes_received_count = recv(_socket, buffer, BUFFER_SIZE_IN_BYTES - total_bytes_received, 0);
        if (bytes_received_count == 0) break;
        printf("Response message: %d bytes: %s\n", bytes_received_count, buffer);
        total_bytes_received = total_bytes_received + bytes_received_count;
    }
    close(_socket);
    return 0;
}
