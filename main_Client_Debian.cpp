#include <iostream>
#include <string>
#include <cstring>      // For std::strerror()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>     // For close()

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <message>" << endl;
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
    server.sin_port = htons(54000);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
        perror("inet_pton() failed");
        close(sockfd);
        return 1;
    }

    // Send the message
    string s(argv[1]);
    ssize_t bytesSent = sendto(sockfd, s.c_str(), s.size() + 1, 0, (struct sockaddr*)&server, sizeof(server));
    if (bytesSent == -1) {
        perror("sendto() failed");
        close(sockfd);
        return 1;
    }

    cout << "Message sent: " << s << endl;

    // Close the socket
    close(sockfd);

    return 0;
}
