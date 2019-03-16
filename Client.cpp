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
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    struct sockaddr_in addr;
    int socketClient = socket(AF_INET,SOCK_STREAM,0);
    if (socketClient < 0) 
    {
        cout << "Bad socket!"<<endl;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1488);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(socketClient,(struct sockaddr*)&addr,sizeof(addr));

    while(1)
    {
        char buff[4096];
        cin>> buff;
        int result = send(socketClient,buff,sizeof(buff),0);
        if (result == -1) 
        {
            cout<<"Server was fall"<<endl;
            return 0;
        }
        
        string str(buff);
        if(str == "exit")
        {
            return 0;
        }
    }
    


    return 0;
}