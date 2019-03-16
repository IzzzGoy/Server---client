#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;

void* SelfServis(void*);



chrono::time_point<chrono::system_clock> start;


int main()
{

    chrono::time_point<chrono::system_clock> end; 
    ///////
    struct sockaddr_in addr;
    int serverSock = socket(AF_INET,SOCK_STREAM,0);
    fcntl(serverSock, F_SETFL, O_NONBLOCK);///Помни, это только, если while будет рaботать по таймеру chrono
    if(serverSock == -1)
    {
        cout<<"Bad socket!"<<endl;
        exit(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1488);
    addr.sin_addr.s_addr = INADDR_ANY;
    int bindStatus = bind(serverSock,(struct sockaddr*)&addr,sizeof(addr));
    
    if (bindStatus == -1) 
    {
        cout<<"Bad bind!"<<endl;
        exit(-1);
    }
    listen(serverSock,10);
    start = chrono::system_clock::now();
    end = chrono::system_clock::now();
    while(chrono::duration_cast<std::chrono::seconds>(end-start).count() < 30)
    {
        int acceptSocket = accept(serverSock,0,0);
        if (acceptSocket > 0) 
        {
            int result;
            int* arg = new int[1];
            arg[0] = acceptSocket;
            pthread_t tmp;
            pthread_create(&tmp,0,SelfServis,(void*)arg);
            start = chrono::system_clock::now();
        }
        end = chrono::system_clock::now();    
        this_thread::sleep_for(200ms);        
    }
    
    cout<<"Timeout!"<<endl;
    
    return 0;
}


void* SelfServis(void* args)
{
    char buff[4096];
    int* _args = (int*)args;
    while(1)
    {
        int input = recv(_args[0],buff,4096,0);
        if(input > 0)
        {
            string str(buff);
            if( str == "exit")
            {
                close(_args[0]);
                pthread_exit(0);
            }
            cout<<buff<<endl;
            start = chrono::system_clock::now();
        }
    }
    return 0;
}
