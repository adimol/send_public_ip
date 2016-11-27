#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int udpSocket, nBytes, port;
    char *buffer[10]; // buffer that maintains last 10 IP entries
    char *save_last;
    struct sockaddr_in server_addr;
    int client_len;
    FILE *fp;

    //allocate the buffer and initialise to 0
    for (int i = 0; i < 10; i++) {
        buffer[i] = NULL;
        while (buffer[i] == NULL)
            buffer[i] = (char *)calloc(120, sizeof(char)); // 120 for safety
    }

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
    int yes = 1;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    /*Bind socket with address struct*/
    bind(udpSocket, (struct sockaddr *) &server_addr, sizeof(server_addr));

    while(1) {
        // shift (rotate) elements of array to right, allowing a new string on pos 0;
        // first element becomes the previous last element
        save_last = buffer[9];
        for (int i = 9; i >= 1; i--)
            buffer[i] = buffer[i-1];
        buffer[0] = save_last;

        // wait for incoming UDP socket
        // in case of error, make sure string ends at length 100 (even though
        // rest of elements to 120 should be calloced to 0)
        nBytes = recv(udpSocket, buffer[0], 100, 0);
        buffer[0][99] = '\0';

        // keep trying to open file until succeed
        fp = NULL;
        while (fp == NULL)
            fp = fopen("out_ip", "w");

        // write contents to file
        fprintf(fp, "%s\n\n", "Bellow are the latest 10 ips, first is most recent");
        for (int i = 0; i < 10; i++)
            fprintf(fp, "%s\n", buffer[i]);

        fclose(fp);
    }
}
