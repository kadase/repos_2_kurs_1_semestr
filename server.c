#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
    int sock_server = socket(AF_INET, SOCK_STREAM, 0); 
    SAFE("ERROR with socket server", sock_server)
    struct sockaddr_in adr;
    memset(&adr, '0', sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(argv[1])); /*функция, хост ту...(значение порта на хосте и в сети может иметь разный порядок байт)
    у нас от хоста к сети*/
    SAFE("ERROR with bind",bind(sock_server, (struct sockaddr *) &adr, sizeof adr))
    SAFE("ERROR with listen",listen(sock_server, sizeof(adr.sin_port)))
    int adrlen = sizeof adr;
    int fd = accept(sock_server, (struct sockaddr *) &adr, &adrlen);
    SAFE("ERROR with accept", fd)
    int n_read;
    char buf[256];
    n_read = read(fd, buf, 256);
    SAFE("ERROR with read", n_read)
    if (n_read == 0) 
    {
        printf("END OF FILE occured\n");
    }
    write(2, buf, n_read);
    write(fd, buf, n_read);
    write(2, "I've read your message, bro\n", 28);
    sleep(10);
    close(fd);
    close(sock_server);
    return 0;
}