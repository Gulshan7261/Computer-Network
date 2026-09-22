#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock;

    struct sockaddr_in server_addr;

    char student_id[20];
    char file_data[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Open data.txt
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        perror("Unable to open data.txt");
        close(sock);
        exit(1);
    }

    // Read file
    size_t bytes_read =
        fread(file_data, 1, sizeof(file_data) - 1, fp);

    file_data[bytes_read] = '\0';

    fclose(fp);

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1",
              &server_addr.sin_addr);

    // Connect
    if (connect(sock,
                (struct sockaddr*)&server_addr,
                sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        close(sock);
        exit(1);
    }

    printf("Connected to server.\n");

    // Ask Student ID
    printf("Enter Student ID to search : ");
    scanf("%19s", student_id);

    // Send Student ID
    write(sock, student_id, strlen(student_id) + 1);

    // Send file data
    write(sock, file_data, strlen(file_data) + 1);
    

    // Receive response
    int n = read(sock, response,
                 sizeof(response) - 1);

    if (n > 0)
    {
        response[n] = '\0';

        printf("Server Response : %s\n",
               response);
    }

    close(sock);

    return 0;
}