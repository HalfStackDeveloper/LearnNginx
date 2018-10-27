
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/event.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <string.h>
#include "client.hpp"

using namespace std;


void startClient()
{
    for(int i = 1; i< 5; i++) {
        thread thread(startClientId,i);
        thread.detach();
        sleep(3);
    }
    while (1) {
        ;
    }
}


void startClientId(int clientId)
{
    //sleep(2);
    
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向Server发起请求
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(9999);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    while (true) {
        //向服务器传送数据
        string s = "I am Client ";
        s.append(to_string(clientId));
    
        char str[60];
        strcpy(str,s.c_str());
        write(sock, str, strlen(str));
        
        //读取服务器传回的数据
        char buffer[60];
        if(read(sock, buffer, sizeof(buffer)-1)>0){
            printf("Client %d receive : %s\n",clientId,buffer);
        }
        
        sleep(9);
    }
}
