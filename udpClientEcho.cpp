#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define MAX_BUFFER_SIZE 1024
#define MAX_LIMIT 100
int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char message[MAX_LIMIT];
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("Enter Message :");
        fgets(message, MAX_LIMIT, stdin);
        if ((sendto(sock, message, strlen(message), MSG_CONFIRM, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0))
        {
            perror("Some error occured");
            break;
        }
        if (strcmp(message, ":q") == 0)
        {
            break;
        }
        printf("Message sent to server: %s", message);
        if ((valread = recvfrom(sock, buffer,
                                MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&serv_addr, &(int){sizeof(serv_addr)}) < 0))
        {
            perror("some error occured");
            break;
        };
        printf("Message received from server: %s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }
    close(sock);
    return 0;
}
