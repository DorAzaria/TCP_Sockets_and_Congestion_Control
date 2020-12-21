#include <stdio.h>
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 5060
#define SERVER_IP_ADDRESS "127.0.0.1"

int main() {

    // SOCK_STREAM = a TCP protocol type.
    // AF_INET = IPv4.
    int my_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(my_socket == -1) {
        printf("Couldn't create the socket : %d", errno);
    }

    struct sockaddr_in server_address;
    // used to clean the array by zeros.
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    // short, network byte order converter.
    server_address.sin_port = htons(SERVER_PORT);

    // convert the IP address from String type.
    int rval = inet_pton(AF_INET, (const char*)SERVER_IP_ADDRESS, &server_address.sin_addr);
    if(rval <= 0) {
        printf("inet_pton() failed");
        return -1;
    }

    // Make a connection to the server with socket SendingSocket.
    int connection = connect(my_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(connection == -1) {
        printf("connect() failed with error code : %d", errno);
    }

    printf("connected to server\n");

    // Sends some data to server
    char message[] = "Good morning, Vietnam\n";
    int messageLen = strlen(message) + 1;

    int bytesSent = send(my_socket, message, messageLen, 0);

    if (-1 == bytesSent) {
	    printf("send() failed with error code : %d" ,errno);
    }
    else if (0 == bytesSent) {
	    printf("peer has closed the TCP connection prior to send().\n");
    }
    else if (messageLen > bytesSent) {
	    printf("sent only %d bytes from the required %d.\n", messageLen, bytesSent);
    }
     else {
	    printf("message was successfully sent .\n");
    }

	sleep(3);
	 
    // TODO: All open clientSocket descriptors should be kept
    // in some container and closed as well.
    close(my_socket);
    return 0;
}