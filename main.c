

/******* 客户端程序 client.c ************/ 
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



int main (int argc, char *argv[]) 
{
    
    int sockfd; 
    unsigned long flag=1;
    char buffer[1024]; 
    struct sockaddr_in server_addr; 
    char *host; 
    int portnumber, nbytes; 
    int i=0;
    char cmd[10][200];
    int ret=1;
    
    struct fd_set fdsets;
    struct timeval tv;
    
    /**************************** 参数检查 ********************************/ 
    if (argc != 5) 
    
    {
    
        fprintf (stderr,"Usage:%s hostname portnumberan", argv[0]); 
        
        return ret;//exit (1); 
    
    }
    

    if((host = argv[1]) == NULL) 
    {
        
        fprintf (stderr,"%s,Gethostname errorn",argv[1]); 
    
        return ret;//exit (1); 
    
    }
    
    if ((portnumber = atoi (argv[2])) < 0) 
    
    {
    
        fprintf (stderr,"Usage:%s hostname portnumberan", argv[0]); 
        
        return ret;//exit (1); 
    
    }
    
    if((argv[3]) == NULL) 
    {
        
        fprintf (stderr,"%s,server errorn",argv[3]); 
    
        return ret;//exit (1); 
    
    }
    
    if((argv[4]) == NULL) 
    {
        
        fprintf (stderr,"%s,filename errorn",argv[4]); 
    
        return ret;//exit (1); 
    
    }
    
    
     /**************************** socket 初始化 ********************************/ 
     
    //初始化 DLL
    WSADATA wsaData;
    //WSAStartup( MAKEWORD(2, 2), &wsaData);
    
     if(WSAStartup(MAKEWORD(2,1),&wsaData))// windows socket dll;
     {
        printf("Winsock initiate failed!!/n");
        WSACleanup();
        return ret;//return 0;
     }

    
    if ((sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) 
    {
    
        fprintf (stderr,"Socket Error:%san", strerror (errno)); 
    
        goto out;//exit (1); exit (1); 
    
    }
    /*
    if(ioctlsocket(sockfd,FIONBIO,(unsigned long *)&flag) != NO_ERROR)     //设置非阻塞模式 
    { 
        //closesocket(sockfd); 
        goto out; 
    }
    */
   
    
    //bzero (&server_addr, sizeof (server_addr)); 
    memset(&server_addr, 0,sizeof (server_addr));
    server_addr.sin_family = AF_INET; 
    
    server_addr.sin_port = htons (portnumber); 
    
    server_addr.sin_addr.s_addr  = inet_addr(argv[1]); 
    
    
    if (connect(sockfd, (struct sockaddr *) (&server_addr), sizeof (struct sockaddr_in)) == -1) 
    {
    
        fprintf (stderr,"Connect Error:%san", strerror (errno)); 
    
        goto out;//exit (1); 
    }
    
    tv.tv_sec = 1;//秒 
    tv.tv_usec = 0; //微妙 
    FD_ZERO(&fdsets); 
    FD_SET(sockfd,&fdsets);
    
    
     /**************************** 数据写函数 ********************************/ 
    
    
    sprintf(cmd[0],"root\r\n");
    sprintf(cmd[1],"cd /mnt\r\n");
    sprintf(cmd[2],"ls\r\n");
    sprintf(cmd[3],"tftp -g -r %s %s\r\n",argv[4],argv[3]);
    sprintf(cmd[4],"md5sum %s\r\n",argv[4]);
    sprintf(cmd[5],"chmod 777 %s\r\n",argv[4]);
    sprintf(cmd[6],"sh %s\r\n",argv[4]);
    sprintf(cmd[7],"ls -a\r\n");
    /*
    for(i=0;i<2;i++)
    {
        
     if ((nbytes = recv (sockfd, buffer, 1024,0)) == -1) 
    {
    
        fprintf (stderr,"Read Error:%sn", strerror (errno));  
        break;//exit (1); 
    
    }else{
        buffer[nbytes] = '\0';
        printf("%s\n",buffer);   
    }
    
    }
    */

    for(i=0;i<8;i++)
    {
        Sleep(100);    
        if(send(sockfd, cmd[i], strlen(cmd[i]),0) == SOCKET_ERROR)
        {
            printf ("send root Error:%san", strerror (errno));    
            closesocket(sockfd); 
            //终止 DLL 的使用
            WSACleanup();
            break;//exit(1);
        }
    //Sleep(1000);    
    /*
    if ((nbytes = recv (sockfd, buffer, 1024,0)) == -1) 
    {
    
        fprintf (stderr,"Read Error:%sn", strerror (errno));  
        break;//exit (1); 
    
    }else{
        buffer[nbytes] = '\0';
        printf("%s\n",buffer);   
    }
    */
   
    
  /*
    if(send(sockfd, "cd /mnt\r\n", strlen("cd /mnt\r\n"),0) == SOCKET_ERROR)
    {
        printf ("send root Error:%san", strerror (errno));    
        closesocket(sockfd); 
        //终止 DLL 的使用
        WSACleanup();
        exit(1);
    }
    
    
    if(send(sockfd, "ls\r\n", strlen("ls\r\n"),0) == SOCKET_ERROR)
    {
        printf ("send root Error:%san", strerror (errno));    
        closesocket(sockfd); 
        //终止 DLL 的使用
        WSACleanup();
        exit(1);
    }
    
   
    if(send(sockfd, "tftp -g -r t.txt 192.168.100.133\r\n", strlen("tftp -g -r t.txt 192.168.100.133\r\n"),0) == SOCKET_ERROR)
    {
        printf ("send root Error:%san", strerror (errno));    
        closesocket(sockfd); 
        //终止 DLL 的使用
        WSACleanup();
        exit(1);
    }
    */
    }
    
    
     /**************************** 数据读函数 ********************************/ 
    
    for(i=0;i<10;i++){
        if(select(sockfd+1,&fdsets,NULL,NULL,&tv)) {
            if(FD_ISSET(sockfd,&fdsets)){
                 if ((nbytes = recv (sockfd, buffer, 1024,0)) == -1) 
                {
            
                    fprintf (stderr,"Read Error:%sn", strerror (errno));  
                    //break;//exit (1); 
            
                 }else{
                    buffer[nbytes] = '\0';
                    if(strstr(buffer,"SUCCESS_FLAG")){
                       //printf("update success!i=%d\n",i);    
                       ret = 0; 
                    }
                    /* 
                    printf("A NEW LINE!i=%d\n",i);   
                    buffer[nbytes] = '\0';
                    printf("%s\n",buffer);*/   
                }  
            }
        }              
    }
   
    //while(1);
out:    
    closesocket(sockfd); 
     //终止 DLL 的使用
    WSACleanup();
    
    //system("pause");	
    //Sleep(5000);
    //exit (0); 
    return ret;

}
