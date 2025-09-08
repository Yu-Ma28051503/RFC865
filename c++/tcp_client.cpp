/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * TCP Client code
*/

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <getopt.h>

#include "common.hpp"

static int tcpClient(void)
{
    int ret = SUCCESS;
    int sockfd = 0;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t n = 0;

    /* Create socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        ret = ERROR;
    }

    if (ret == SUCCESS) {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            ret = ERROR;
        }
    }

    /* Connect to server */
    if (ret == SUCCESS) {
        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection to server failed" << std::endl;
            ret = ERROR;
        }
    }

    /* Receive quote */
    if (ret == SUCCESS) {
        memset(buffer, 0, sizeof(buffer));
        n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
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
            rfc865Description(1);
            return SUCCESS;
        default:
            printHelp(argv[0]);
            return ERROR;
        }
    }

    ret = tcpClient();
    if (ret == SUCCESS) {
        std::cout << "==============================" << std::endl;
        std::cout << "Let's do our best again today!" << std::endl;
    }
    else {
        std::cerr << "Error: " << ret << std::endl;
    }

    return ret;
}
