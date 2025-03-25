#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define MAX_BUFFER_SIZE 1024
int main()
{
    int server_fd, client_fd, valread;
    struct sockaddr_in serv_addr, clie_addr;
    int addrlen = sizeof(serv_addr);
    char buffer[MAX_BUFFER_SIZE] = {0};
    int len;
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
        0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Echo server listening on port %d\n", PORT);
    while (1)
    {
        if ((valread = recvfrom(server_fd, buffer, MAX_BUFFER_SIZE,
                                MSG_WAITALL, (struct sockaddr *)&clie_addr, &len)) < 0)
        {
            perror("some error occured");
            break;
        }
printf("Received message from client %s:%d :
%s",inet_ntoa(clie_addr.sin_addr),clie_addr.sin_port,buffer);
if (strcmp(buffer, ":q") == 0)
{
            break;
}
sendto(server_fd, buffer, strlen(buffer), MSG_CONFIRM,(struct
sockaddr *)&clie_addr,len);
printf("Echo message sent to client\n");
memset(buffer, 0, MAX_BUFFER_SIZE);
    }
    close(server_fd);
    return 0;
}
