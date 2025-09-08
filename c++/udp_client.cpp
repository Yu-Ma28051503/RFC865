/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * UDP Client code
*/

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <getopt.h>

#include "common.hpp"

static int udpClient(void)
{
    int ret = SUCCESS;
    int sockfd = 0;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    const char *msg = "";  // Empty message as per RFC865
    char buffer[BUFFER_SIZE];
    ssize_t n = 0;
    
    /* Create socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        ret = ERROR;
    }
    else {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            ret = ERROR;
        }
    }

    /* Send empty datagram to server to request a quote */
    if (ret == SUCCESS) {
        if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Send to server failed" << std::endl;
            ret = ERROR;
        }
    }

    /* Receive quote */
    if (ret == SUCCESS) {
        addr_len = sizeof(server_addr);
        memset(buffer, 0, sizeof(buffer));
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server_addr, &addr_len);
        if (n < 0) {
            std::cerr << "Receive failed" << std::endl;
            ret = ERROR;
        }
        else {
            buffer[n] = '\0';
            std::cout << "Quote of the Day: " << buffer << std::endl;
        }
    }

    /* Clean up */
    if (sockfd > 0) {
        close(sockfd);
    }

    return ret;
}

int main(int argc, char *argv[])
{
    int ret = SUCCESS;
    int ch;

    while ((ch = getopt(argc, argv, "46hd")) != -1) {
        switch (ch) {
        case '4':
            /* For future IPv4/IPv6 support */
            break;
        case '6':
            /* For future IPv4/IPv6 support */
            break;
        case 'h':
            printHelp(argv[0]);
            return SUCCESS;
        case 'd':
            rfc865Description(0);
            return SUCCESS;
        default:
            printHelp(argv[0]);
            return ERROR;
        }
    }

    ret = udpClient();

    return ret;
}
