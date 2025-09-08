/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * UDP Server code
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>

#include "common.hpp"

static int udpServer(void)
{
    int ret = SUCCESS;
    int sockfd = 0;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[BUFFER_SIZE];
    char timebuf[64];
    ssize_t len = 0;
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
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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

    /* Main loop to receive datagrams and respond with quotes */
    if (ret == SUCCESS) {
        std::cout << "UDP Quote of the Day Server is running on port " << SERVER_PORT << std::endl;
        while (1) {
            client_addr_len = sizeof(client_addr);
            memset(&client_addr, 0, sizeof(client_addr));
            memset(buffer, 0, sizeof(buffer));

            /* Receive datagram */
            ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
            if (n < 0) {
                std::cerr << "Receive from client failed" << std::endl;
                ret = ERROR;
                continue;  // Continue to next iteration to keep server running
            }

            /* Log received request */
            std::cout << "Received request from user=" << inet_ntoa(client_addr.sin_addr)
                      << " quote_id=" << ntohs(client_addr.sin_port)
                      << " bytes=" << n << std::endl;
            
            /* Prepare quote */
            now = time(NULL);
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
                continue;
            }

            /* If the day has changed, get a new quote */
            tm_info = localtime(&now);
            if (tm_info != NULL && tm_info->tm_yday != today) {
                quote = getRandomQuote();
                today = tm_info->tm_yday;
            }

            /* Send quote back to client */
            sent_len = sendto(sockfd, buffer, len, 0, (struct sockaddr *)&client_addr, client_addr_len);
            if (sent_len < 0) {
                std::cerr << "Send to client failed" << std::endl;
                ret = ERROR;
            }
            else {
                /* Log successful delivery */
                std::cout << "Quote delivered to user=" << inet_ntoa(client_addr.sin_addr)
                          << " quote_id=" << ntohs(client_addr.sin_port)
                          << " bytes=" << sent_len << std::endl;
            }
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
            rfc865Description(0);  // 0 for UDP
            return SUCCESS;
        default:
            printHelp(argv[0]);
            return ERROR;
        }
    }

    ret = udpServer();

    return ret;
}
