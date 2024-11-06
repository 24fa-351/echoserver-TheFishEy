#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 46645
#define LISTEN_BACKLOG 5

void handleConnection(int client_socket) {
    char buffer[1024];
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    write(client_socket, buffer, bytes_read);
}

int main(int argc, char *argv[]) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    int result;

    result = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    result = listen(server_socket, LISTEN_BACKLOG);

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    handleConnection(client_socket);

    return 0;
}
