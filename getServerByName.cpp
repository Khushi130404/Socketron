#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

int main()
{
    struct servent *se;
    const char *name;
    const char *proto;

    name = (char *)malloc(sizeof(char) * 100);
    proto = (char *)malloc(sizeof(char) * 100);

    printf("Enter name of service : ");
    scanf("%s", name);

    printf("\nEnter protocol name : ");
    scanf("%s", proto);

    se = getservbyname(name, proto);

    if (se == NULL)
    {
        printf("Service not found\n");
        exit(1);
    }

    printf("Service name: %s\n", se->s_name);
    printf("Port number: %d\n", ntohs(se->s_port));
    printf("Protocol: %s\n", se->s_proto);

    return 0;
}
