#include <iostream>
#include <ws2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std; // Saves us from typing std::cout << etc. etc. etc.

int main(int argc, char* argv[]) // We can pass in a command line option!!
{
    if (argc < 2) {
    cout << "Usage: " << argv[0] << " <message>" << endl;
    return 1;
    }

    // Start up win sock
    WSADATA data;
    WORD version = MAKEWORD (2, 2);
    int wsOk = WSAStartup(version, &data);
    if (wsOk != 0)
    {
        cout << "Can't start Winsock!" << wsOk;
        return 1;
    }
    // Create a hint structure for the server
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);

    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    // Socket creation
    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    // Write out to that socket
    string s(argv[1]);
    int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));

    if (sendOk == SOCKET_ERROR)
    {
        cout << " That didn't work! " << WSAGetLastError() << endl;
    }

    // Close the socket
    closesocket(out);

    // close down winsock
    WSACleanup();
    
    cout << "Message sent: " << s << endl;
}
