#include <iostream>
#include <fstream>
#include <string>
#include <cstring>      // For std::strerror()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>     // For close()

using namespace std;

int main() {
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        cerr << "Error creating socket: " << strerror(errno) << endl;
        return 1;
    }

    // Bind the socket to a specific address and port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(52010);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == $
        cerr << "Error binding socket: " << strerror(errno) << endl;
        close(sockfd);
        return 1;
    }

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[1024];
    ofstream TransmissionLog("TransmissionLog.txt");

    if (!TransmissionLog.is_open()) {
        cerr << "Failed to open TransmissionLog.txt for writing." << endl;
        close(sockfd);
        return 1;
    }

    cerr << "Waiting to receive a file..." << endl;
    while (true) {
 memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, (str$
        if (bytesReceived == -1) {
            cerr << "Error receiving data: " << strerror(errno) << endl;
            continue;
        }
        if (std::string(buffer) == "END_OF_FILE_MARKER") {
            cout << "Received the file and successfully transferred to Desti$
            string msr = "MSR";
            sendto(sockfd, msr.c_str(), msr.size() + 1, 0, (struct sockaddr*$
            break;
        }
        TransmissionLog << buffer << endl;
    }

    close(sockfd);
    TransmissionLog.close();

    return 0;
}
