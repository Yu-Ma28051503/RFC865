/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * TCP Server code
*/

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <getopt.h>
#include <time.h>

#include "common.hpp"

static int tcpServer(void)
{
    int ret = SUCCESS;
    int sockfd = 0;
    int connfd = 0;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[BUFFER_SIZE];
    char timebuf[64];
    int len = 0;
    ssize_t sent_len = 0;
    time_t now;
    struct tm *tm_info;
    const char *quote = getRandomQuote();
    int today = 0;

    /* save got quote day */
    now = time(NULL);
    tm_info = localtime(&now);
    if (tm_info != NULL) {
        today = tm_info->tm_yday;
    }

    /* Create socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        ret = ERROR;
    }
    else {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(SERVER_PORT);
    }

    /* Bind socket */
    if (ret == SUCCESS) {
        if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Bind failed" << std::endl;
            ret = ERROR;
        }
    }

    /* Listen */
    if (ret == SUCCESS) {
        if (listen(sockfd, 5) < 0) {
            std::cerr << "Listen failed" << std::endl;
            ret = ERROR;
        }
    }

    /* Accept and handle connections */
    if (ret == SUCCESS) {
        std::cout << "TCP Server is running on port " << SERVER_PORT << "..." << std::endl;
        while (1) {
            client_addr_len = sizeof(client_addr);
            if ((connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
                std::cerr << "Accept failed" << std::endl;
                ret = ERROR;
                break;
            }

            /* Check if we need to get a new quote for the day */
            now = time(NULL);
            tm_info = localtime(&now);
            if (tm_info != NULL && tm_info->tm_yday != today) {
                quote = getRandomQuote();
                today = tm_info->tm_yday;
            }

            /* Prepare quote with timestamp */
            if (ctime_r(&now, timebuf) != NULL) {
                char *nl = strchr(timebuf, '\n');
                if (nl) {
                    *nl = '\0';
                }
            } else {
                strncpy(timebuf, "unknown-time", sizeof(timebuf)-1);
                timebuf[sizeof(timebuf)-1] = '\0';
            }
            memset(buffer, 0, sizeof(buffer));
            len = snprintf(buffer, sizeof(buffer), "Quote of the Day: %s\n%s\n", timebuf, quote);
            if (len < 0 || len >= (int)sizeof(buffer)) {
                std::cerr << "Quote formatting failed" << std::endl;
                ret = ERROR;
                close(connfd);
                continue;
            }

            if (ret != SUCCESS) {
                close(connfd);
                continue;
            }

            /* Send quote */
            sent_len = send(connfd, buffer, len, 0);
            if (sent_len < 0) {
                std::cerr << "Send failed" << std::endl;
                ret = ERROR;
            }

            close(connfd);
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

    ret = tcpServer();
    if (ret == SUCCESS) {
        std::cout << "==============================" << std::endl;
        std::cout << "Let's do our best again today!" << std::endl;
    }
    else {
        std::cerr << "An error occurred in the TCP server." << std::endl;
    }

    return ret;
}
