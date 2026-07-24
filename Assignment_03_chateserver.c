#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *message = "Hello from server";

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Define address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    // 3. Bind socket
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  
// 4. Listen for connections
    listen(server_fd, 3);
    while(1){
   
        for(int i=0;i<='\0';i++){
            buffer[i]='\0';
        }

    printf("Server waiting on port %d...\n", PORT);

    // 5. Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // 6. Read from client
    read(new_socket, buffer, 1024);
    printf("Client: %s\n", buffer);

    // 7. Send response
    // memset(buffer, 0, sizeof(buffer)); // Clear buffer before sending response
    // strcpy(buffer, message); // Copy the message to buffer 
    scanf("%[\n]",buffer);
    if(strcmp(buffer, message)==0)
    // Compare buffer with message (not necessary here, but included for demonstration)
    send(new_socket, buffer, strlen(buffer), 0);

}
    close(new_socket);
    close(server_fd);

    return 0;
}