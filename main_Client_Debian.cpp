#include <iostream>
#include <string>
#include <fstream>
#include <cstring>      // For std::strerror()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>     // For close()

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <server-name> <server-port> <sourc$
        return 1;
    }

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        return 1;
    }

    // Set up the server details
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(stoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &server.sin_addr) <= 0) {
        perror("inet_pton() failed");
        close(sockfd);
        return 1;
    }

    // Opening the file
    ifstream in(argv[3]); // the in flag is optional

    if (!in) {
        cerr << "Failed to open" << argv[3] << endl;
        return 1;
    }
//Send the message
    string s;
    while (getline(in, s)){
        ssize_t bytesSent = sendto(sockfd, s.c_str(), s.size() + 1, 0, (stru$
        if (bytesSent == -1) {
                perror("sendto() failed");
                close(sockfd);
                return 1;
        }
    }

    string eof = "END_OF_FILE_MARKER";
    sendto(sockfd, eof.c_str(), eof.size() + 1, 0, (struct sockaddr*)&server$

    cout << "File is sent successfully" << endl;
    cout << "Waiting for confirmation..." << endl;

    char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, null$
        if (bytesReceived > 0 && string(buffer) == "MSR") {
            cout << "File recieved successfully" << endl;
        }
    close(sockfd);
    return 0;
}
