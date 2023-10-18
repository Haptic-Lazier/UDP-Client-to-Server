#include <iostream>
#include <ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std; // Saves us from typing std::cout << etc. etc. etc.

int main()
{
    // Start up win sock
    WSADATA data;
    WORD version = MAKEWORD (2, 2);
    int wsOk = WSAStartup(version, &data);
    if (wsOk != 0)
    {
        cout << "Can't start Winsock!" << wsOk;
        return 1;
    }

    // Bind Socket to IP address and port

    SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in ServerHint;
    ServerHint.sin_addr.S_un.S_addr = ADDR_ANY;
    ServerHint.sin_family =AF_INET;
    ServerHint.sin_port = htons(54000); // Convert from little to big endian

    if (bind(in, (sockaddr*)&ServerHint, sizeof(ServerHint)) == SOCKET_ERROR)
    {
        cout << "Can't bind Socket!" << WSAGetLastError() << endl;
        return 1;
    }

    sockaddr_in client;
    int clientLength = sizeof(client);
    ZeroMemory(&client, clientLength);

    char buf[1024];

    // Enter a loop
    while (true)
    {
        ZeroMemory(buf, 1024);
        // Wait for a message
        int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
        if (bytesIn == SOCKET_ERROR)
        {
            cout << "Error recieving from client" << WSAGetLastError() << endl;
            continue; 
        }
        // display message and client info
        char clientIp[256];
        ZeroMemory(clientIp, 256);

        inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

        cout << "Mesage recv from " << clientIp << " : " << buf << endl;
    }
    //close socket and shutdown winsock
    closesocket(in);
    WSACleanup();
    return 0;
}
