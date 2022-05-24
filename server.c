#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include "common.c"


int main(int argc, char *argv[]) {
    struct order_context *equipments = initialize_empty_orders();
    if (argc < 3) print_server_usage_pattern();
    struct socket_context context = initialize_server_socket(argv[1], argv[2]);
    int _socket = context.socket;
    while (1) {
        int *sensor_ids = NULL;
        struct sockaddr_storage client_socket_storage;
        struct sockaddr *client_socket_address = (struct sockaddr *) (&client_socket_storage);
        int client_socket_address_len = sizeof(*client_socket_address);
        int client_socket = accept(_socket, client_socket_address, (socklen_t *) &client_socket_address_len);
        if (client_socket < FALSE) error("Error with client socket communication...");
        const char *client_socket_ip = inet_ntoa(((struct sockaddr_in *) &client_socket_address)->sin_addr);
        printf("Connection from: %s established!\n", client_socket_ip);
        char buffer[BUFFER_SIZE_IN_BYTES] = {};
        memset(buffer, 0, BUFFER_SIZE_IN_BYTES);
        size_t count = recv(client_socket, buffer, BUFFER_SIZE_IN_BYTES - 1, 0);
        printf("Message received from %s: %d bytes: %s\n", client_socket_ip, (int) count, buffer);
        char buffer_copy[BUFFER_SIZE_IN_BYTES] = {};
        strcpy(buffer_copy, buffer);
        const char *command = strtok(buffer_copy, " ");
        sensor_ids = get_sensor_ids_from_message(buffer);
        int equipment_id = get_equipment_id_from_message(buffer);
        if (is_equal(command, ADD)) {
            handle_add_message(client_socket_address, client_socket, equipments, sensor_ids, equipment_id);
        }
        if (is_equal(command, REMOVE)) {
            handle_remove_message(client_socket_address, client_socket, equipments, sensor_ids, equipment_id);
        }
        if (is_equal(command, LIST)) {
            handle_list_message(client_socket_address, client_socket, equipments, sensor_ids, equipment_id);
        }
//        if (is_equal(command, REMOVE)) {
//            const int sensor_id = (int) buf[11] - ASCII_INTEGER_START_INDEX;
//            const int equipment_id = (int) buf[16] - ASCII_INTEGER_START_INDEX;
//            char response_buffer[BUFFER_SIZE_IN_BYTES] = {};
//            struct order_context order;
//            order.equipment_id = equipment_id;
//            order.sensor_id = sensor_id;
//            equipments[SERVER_EQUIPMENTS_COUNT] = order;
//            sprintf(response_buffer, "sensor %d added\n", sensor_id);
//            count = send(client_socket, response_buffer, strlen(response_buffer) + 1, 0);
//            printf("Message send for %s: %d bytes: %s\n", client_socket_ip, (int) count, response_buffer);
//            if (count != strlen(response_buffer) + 1) error("Error sending response message...");
//            close(client_socket);
//        }
//        sprintf(buf, "remote endpoint: %s\n", request_buffer);
    }
}