#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>


main()
{
    int socketClient;
    int connection;
    char buff[1024];
    struct sockaddr_in addr;
              
    if((socketClient = socket(AF_INET,SOCK_STREAM,0)) < 0)
        {
            perror("Bad socket");
            exit(-1);
        }
    //fcntl(socketClient, F_SETFL, O_NONBLOCK); 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1488);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if((connection = connect(socketClient, (struct sockaddr*) &addr, sizeof(addr))) < 0)
    {
        perror("Bad connection");
        exit(-1);
    }
    std::cout << "Server socket numb is " << connection << std::endl;

    //fcntl(socketClient, F_SETFL, O_NONBLOCK); 
    while(1)
    {
       

        std::cin >> buff;
        send(socketClient, buff, 1024, 0);
    }
}
