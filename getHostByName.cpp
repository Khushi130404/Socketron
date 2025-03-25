#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        return 1;
    }

    struct hostent *he = gethostbyname(argv[1]);

    if (he == NULL)
    { // get the host info
        herror("gethostbyname");
        return 2;
    }

    struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;

    for (int i = 0; addr_list[i] != NULL; i++)
    {
        printf("%s\n", inet_ntoa(*addr_list[i]));
    }

    return 0;
}
