#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int udpSocket, nBytes, port;
    char buffer[100];
    struct sockaddr_in server_addr;
    int client_len;
    FILE *fp;

    // read the port number
    if (argc < 2) {
        printf("Usage: rec_ip_server <port>\n");
        exit(1);
    }
    port = atoi(argv[1]);

    // open a socket
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    // fill in ip & port of server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

    // if socket already in use by kernel (previously opened), force re-use
    int yes=1;
    if (setsockopt(udpSocket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    /*Bind socket with address struct*/
    bind(udpSocket, (struct sockaddr *) &server_addr, sizeof(server_addr));

    while(1) {
        nBytes = recv(udpSocket,buffer,100,0);
        fp = fopen("out_ip", "w");
        if (fp == NULL)
            exit(1);

        fprintf(fp, "%s\n", buffer);
        fclose(fp);
        // printf("%s\n", buffer); // test by printing buffer in console
    }
}
