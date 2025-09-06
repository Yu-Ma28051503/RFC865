/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * UDP Client code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <getopt.h>

#include "common.h"

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
        fprintf(stderr, "Socket creation failed");
        ret = ERROR;
    }
    else {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        if (inet_pton(AF_INET, SERVER_IPv4, &server_addr.sin_addr) <= 0) {
            fprintf(stderr, "Invalid address/ Address not supported");
            ret = ERROR;
        }
    }

    /* Send empty datagram to server to request a quote */
    if (ret == SUCCESS) {
        if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            fprintf(stderr, "Send to server failed");
            ret = ERROR;
        }
    }

    /* Receive quote */
    if (ret == SUCCESS) {
        addr_len = sizeof(server_addr);
        memset(buffer, 0, sizeof(buffer));
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server_addr, &addr_len);
        if (n < 0) {
            fprintf(stderr, "Receive failed");
            ret = ERROR;
        }
        else {
            buffer[n] = '\0';
            printf("%s", buffer);
        }
    }

    if (sockfd >= 0) {
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
                return ret;
            case 'd':
                rfc865Discription(0);
                return ret;
            case '?':
            default:
                printHelp(argv[0]);
                return ERROR;
        }
    }

    ret = udpClient();
    if (ret != SUCCESS) {
        fprintf(stderr, "UDP Client encountered an error\n");
    }
    else {
        printf("==============================\n");
        printf("Let's do our best again today!\n");
    }

    return 0;
}
