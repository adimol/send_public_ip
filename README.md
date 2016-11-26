# send_public_ip
a server / client program used to send the public ip of a client (that can change over time) to another server (that has a static ip). The server can listen 24/7, while the client can be used with crontab to periodically send its public ip (through UDP sockets). This can be used to remote access (through ssh) the client at any time by knowing its current public ip (client is behind a router with a dynamic ip).

# Usage:

Client:

./send_ip_client \<ip\> \<port\>

sends its public ip to the server's \<ip\> on \<port\>.

Server:

./rec_ip_server \<port\>

listens on the selected \<port\>
