#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_fd)
{
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    int n;

    // Receive Student ID
    n = read(client_fd, buffer, sizeof(buffer) - 1);

    if (n <= 0)
    {
        close(client_fd);
        exit(0);
    }

    buffer[n] = '\0';

    printf("Student ID received: %s\n", buffer);

    // Receive file data
    n = read(client_fd, buffer + 100, sizeof(buffer) - 101);

    if (n <= 0)
    {
        close(client_fd);
        exit(0);
    }

    buffer[n + 100] = '\0';

    char *file_data = buffer + 100;

    // Search Student ID
    char *line = strtok(file_data, "\n");

    int found = 0;

    while (line != NULL)
    {
        char id[20];

        sscanf(line, "%s", id);

        if (strcmp(id, buffer) == 0)
        {
            snprintf(response, sizeof(response),
                     "Record Found : %s", line);

            found = 1;
            break;
        }

        line = strtok(NULL, "\n");
    }

    if (!found)
    {
        strcpy(response, "Record Not Found");
    }

    // Send response
    write(client_fd, response, strlen(response));

    close(client_fd);

    exit(0);
}

int main()
{
    int server_fd;
    int client_fd;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t addr_size;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    printf("Server socket created.\n");

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd,
             (struct sockaddr*)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }

    printf("Server bind successful.\n");

    // Listen
    if (listen(server_fd, 5) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        addr_size = sizeof(client_addr);

        // Accept client
        client_fd = accept(server_fd,
                           (struct sockaddr*)&client_addr,
                           &addr_size);

        if (client_fd < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("Client connected.\n");

        // Create child process
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            close(client_fd);
        }
        else if (pid == 0)
        {
            // Child process

            close(server_fd);

            handle_client(client_fd);
        }
        else
        {
            // Parent process

            close(client_fd);
        }
    }

    close(server_fd);

    return 0;
}