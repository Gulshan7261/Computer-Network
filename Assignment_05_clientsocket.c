/*#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

#define PORT 8081 
#define BUFFER_SIZE 1024 

int main() { 
    int sock; 
    struct sockaddr_in serv_addr; 
    char buffer[BUFFER_SIZE]; 
    char input[BUFFER_SIZE]; 

    // Create Socket---
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); 
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (1) {

        fgets(input, BUFFER_SIZE, stdin);
        printf("Enter request: ");

        // delete newline
        input[strcspn(input, "\n")] = '\0';

        // send request
        send(sock, input, strlen(input), 0);

        if(strcmp(input, "bye")==0)
        break;

        memset(buffer, 0, BUFFER_SIZE);

        // RECIVE
        int valread = read(sock, buffer, BUFFER_SIZE -1);

        if (valread <= 0)
            break;

        buffer[valread] = '\0';


    printf("server response: %s\n", buffer);
    }

    close(sock); 
    return 0; 
}
    */

    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

# define PORT 8080
# define BUFFER_SIZE 1024

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char word[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // inet_pton(AF_INET, "10.158.201.130", &serv_addr.sin_addr);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 3. Connect to server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));


    while (1)
    {
        printf ( "\nEnter Text To ANALYZE ( or type 'bye' to exit ) : " ) ;
        
        fgets ( word , BUFFER_SIZE , stdin );
        send(sock, word, strlen(word), 0);

         if ( strcmp ( word , " bye " ) == 0) {
            printf("Thank u for using our app..");
            break;
        }

       
        printf ( "Server Response  \n" ) ;
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, sizeof(buffer));
        printf("Server: \n %s\n", buffer);
    }
    printf("exit...");

    close(sock);

    return 0;
}