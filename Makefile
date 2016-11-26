CC=gcc
CFLAGS= -O2 -g

all : send_ip_client rec_ip_server

send_ip_client : send_ip_client.o
		$(CC) $(CFLAGS) -o send_ip_client send_ip_client.o

rec_ip_server : rec_ip_server.o
		$(CC) $(CFLAGS) -o rec_ip_server rec_ip_server.o

send_ip_client.o : send_ip_client.c
		$(CC) $(CFLAGS) -c send_ip_client.c

rec_ip_server.o : rec_ip_server.c
		$(CC) $(CFLAGS) -c rec_ip_server.c

clean:
		rm *.o send_ip_client rec_ip_server
