#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define SAFE(msg, call)\
if ((call) == -1)\
{\
    perror(msg);\
    exit(1);\
}\

int main(int argc, char** argv) 
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    SAFE("ERROR with socket client", fd)
    struct sockaddr_in adr;
    memset(&adr, '0', sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(argv[1]));
    SAFE("ERROR with inet_pton",inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr))
    //подключаемся именно к нашему компьютеру
    SAFE("ERROR with connect", connect(fd, (struct sockaddr *) &adr, sizeof adr))
    write(fd, "Hello, Bro\n", 11);
    char buf[256];
    int n_read;
    n_read = read(fd, buf, 256);
    SAFE("ERROR with read", n_read)
    if (n_read == 0) 
    {
        printf("END OF FILE occured\n");
    }
    write(2, buf, n_read);
    sleep(10);
    close(fd);
    return 0;
}