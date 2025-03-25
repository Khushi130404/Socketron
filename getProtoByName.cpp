#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

int main()
{
    char *name;
    int i;
    struct protoent *proto;

    name = (char *)malloc(sizeof(char) * 100);

    printf("Enter protocol name: ");
    scanf("%s", name);

    proto = getprotobyname(name);

    if (proto != NULL)
    {
        printf("Official name: %s\n", proto->p_name);
        printf("Protocol number: %d\n", proto->p_proto);

        for (i = 0; proto->p_aliases[i] != 0; i++)
        {
            printf("Alias[%d]: %s\n", i + 1, proto->p_aliases[i]);
        }
    }
    else
    {
        perror("Protocol not found");
    }

    return 0;
}
