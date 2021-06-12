#define  WIN                // WIN for Winsock and BSD for BSD sockets//===================================================== file = mclient.c =====


//----- Include files -------------------------------------------------------
#include <stdio.h>          // Needed for printf()
#include <stdlib.h>         // Needed for memcpy()
#ifdef WIN
#pragma comment(lib, "Wsock32.lib")
#include <winsock.h>      // Needed for all Windows stuff

#endif
#ifdef BSD
#include <sys/types.h>    // Needed for system defined identifiers.
#include <netinet/in.h>   // Needed for internet address structure.
#include <sys/socket.h>   // Needed for socket(), bind(), etc...
#include <arpa/inet.h>    // Needed for inet_ntoa()
#include <fcntl.h>
#include <netdb.h>
#endif

//#define SERVERPORT 1900
#define SERVERPORT 27000


char buff[] = "Tip: Senzor za temperaturu | Stanje: Aktivan | ID: 1";

int main()
{
    //char buff[400]; 
    char rcvdbuff[1000];
    int len, Ret = 2;

    WSADATA wsaData;
    struct sockaddr_in their_addr;
    struct hostent* he;
    SOCKET sock;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    their_addr.sin_family = AF_INET;

   // their_addr.sin_addr.s_addr = inet_addr("239.255.255.250");   
    their_addr.sin_addr.s_addr = inet_addr("147.91.160.65"); //192.168.1.6
    their_addr.sin_port = htons(SERVERPORT);
    len = sizeof(struct sockaddr_in);

    while (1)
    {
        printf("buff:\n%s\n", buff);

        Ret = sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&their_addr, len);
        if (Ret < 0)
        {
            printf("error in SENDTO() function");
            closesocket(sock);
            return 0;
        }

        //Receiving Text from server
        printf("\n\nwaiting to recv:\n");
        memset(rcvdbuff, 0, sizeof(rcvdbuff));
        Ret = recvfrom(sock, rcvdbuff, sizeof(rcvdbuff), 0, (struct sockaddr*)&their_addr, &len);
        if (Ret < 0)
        {
            printf("Error in Receiving");
            return 0;
        }
        rcvdbuff[Ret - 1] = '\0';
        printf("RECEIVED MESSAGE FROM SERVER\t: %s\n", rcvdbuff);

        //Delay for testing purpose
        Sleep(3 * 1000);
    }
   /* closesocket(sock);
    WSACleanup();
    */
#ifdef WIN
    closesocket(sock);
    WSACleanup();
#endif
#ifdef BSD
    close(sock);
#endif
}
