#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define SERVER_PORT 5060  //The port that the server listens.

int main() {
    // on linux to prevent crash on closing socket.
    signal(SIGPIPE, SIG_IGN);

    // create a socket lisener.
    int socket_listener = -1;
    if((socket_listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Couldn't create a socket listener : %d",errno);
    }

	// setsockopt = used to control the options of this socket.
    // Reuse the port if the server socket on was closed
	// and remains for 45 seconds in TIME-WAIT state till the final removal.
    int enable_reuse = 1;
    if(setsockopt(socket_listener, SOL_SOCKET, SO_REUSEADDR,&enable_reuse, sizeof(int)) < 0) {
        printf("setsockopt() failed with error code: %d", errno);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);  //network order

    // connect the server to a port which can read and write on.
    if(bind(socket_listener, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        printf("Bind failed with error code : %d" , errno);
        return -1;
    }

    printf("Bind() success!\n");

    // Make the socket listening; actually mother of all client sockets.
    // 500 is a Maximum size of queue connection requests
    // number of concurrent connections 
    if(listen(socket_listener, 500) == -1) {
        printf("listen() failed with error code : %d",errno);
        return -1;
    }

    //Accept and incoming connection
    printf("Waiting for incoming TCP-connections...\n");

    struct sockaddr_in client_address;  //
    socklen_t client_address_length = sizeof(client_address);

    while(1) {
        memset(&client_address, 0, sizeof(client_address));

        // updates the length in each iteration.
        client_address_length = sizeof(client_address);

        // accept() gets the connection and return the socket of this connection.
        int client_socket = accept(socket_listener, (struct sockaddr *)&client_address, &client_address_length);
        if(client_socket == -1) {
           printf("listen failed with error code : %d",errno);
        }
        return -1;

        printf("A new client connection accepted\n");

        //Reply to client
        char message[] = "Welcome to our TCP-server\n";
        int messageLen = strlen(message) + 1;
        // this method returns the size of bytes that succesfully sent.
        int bytes_sent = send(client_socket, message, messageLen, 0);
        if(bytes_sent == -1) {
            printf("send() failed with error code : %d", errno); 
        }
        else if(bytes_sent == 0) {
            printf("peer has closed the TCP connection prior to send().\n");
        }
		else if (messageLen > bytes_sent) {
		   printf("sent only %d bytes from the required %d.\n", messageLen, bytes_sent);
		}
        else {
		   printf("message was successfully sent .\n");            
        }
    }

    close(socket_listener);
    return 0;
}