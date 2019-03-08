#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

main()
{
    int socketServer;
    int vizeters[4];
    struct sockaddr_in addr;
    char buff[1024];

    if((socketServer = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("Socket bad");
        exit(-1);
    }

    //fcntl(socketServer, F_SETFL, O_NONBLOCK);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1488);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socketServer,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("Bad bind");
        exit(-1);
    }

    listen(socketServer,4);

    for(size_t i = 0; i < 4; i++)
    {
        if((vizeters[i] = accept(socketServer, NULL, NULL)) < 0)
        {
            perror("Bad connection");
            exit(0);
        }
        fcntl(vizeters[i], F_SETFL, O_NONBLOCK);
        std::cout << "Vizeter from " << vizeters[i] << " has joined!" << std::endl;
    }
    std::cout << "All Users was joined" << std::endl;
    fcntl(socketServer, F_SETFL, O_NONBLOCK);

    while(1)
    {
        std::cout << "We on worked" << std::endl;

        for(size_t i = 0; i < 4;i++)
        {
            //std::cout << "We on worked" << std::endl;
            if(recv(vizeters[i],buff,1024,0) >= 0)
            {
                std::cout << "Catch " << vizeters[i] << std::endl;
                printf("%s\n",buff);
            }
            sleep(1);
            //std::cout << "Now" << std::endl;
        }
    }
    return 0;
}
