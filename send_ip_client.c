#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int udpSocket, port;
    struct sockaddr_in server_addr;
    char buffer[100] = "Hi", server_ip_address[50];

    // read the server ip and port
    if (argc < 3) {
        printf("Usage: send_ip_client <ip> <port>\n");
        exit(1);
    }
    strncpy(server_ip_address, argv[1], 50);
    port = atoi(argv[2]);

    // open a socket
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    // fill in ip & port of server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip_address);
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    int n = sendto(udpSocket, buffer, strlen(buffer) + 1, 0,
        (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (n < 0)
        printf("Error in sendto\n");

}
