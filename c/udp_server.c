/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * UDP Server code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>

#include "common.h"

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
        fprintf(stderr, "Socket creation failed\n");
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
            fprintf(stderr, "Bind failed\n");
            ret = ERROR;
        }
    }

    /* Receive and respond to datagrams */
    if (ret == SUCCESS) {
        printf("UDP Server listening on port %d...\n", SERVER_PORT);
        while (1) {
            ret = SUCCESS;
            client_addr_len = sizeof(client_addr);
            memset(&client_addr, 0, sizeof(client_addr));
            memset(buffer, 0, sizeof(buffer));
            len = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &client_addr_len);
            if (len < 0) {
                fprintf(stderr, "Receive failed\n");
                ret = ERROR;
                continue;
            }

            /* Prepare quote */
            now = time(NULL);
            if (ctime_r(&now, timebuf) != NULL) {
                char *nl = strchr(timebuf, '\n');
                if (nl) {
                    *nl = '\0';
                }
            }
            else {
                strncpy(timebuf, "unknown-time", sizeof(timebuf)-1);
                timebuf[sizeof(timebuf)-1] = '\0';
            }

            /* If the day has changed, get a new quote */
            tm_info = localtime(&now);
            if (tm_info != NULL && tm_info->tm_yday != today) {
                quote = getRandomQuote();
                today = tm_info->tm_yday;
            }

            memset(buffer, 0, sizeof(buffer));
            len = snprintf(buffer, sizeof(buffer), "Quote of the Day: %s\n%s\n", timebuf, quote);
            if (len < 0 || len >= (int)sizeof(buffer)) {
                fprintf(stderr, "Quote formatting failed\n");
                ret = ERROR;
                continue;
            }

            /* Send quote */
            sent_len = sendto(sockfd, buffer, len, 0, (struct sockaddr *)&client_addr, client_addr_len);
            if (sent_len < 0) {
                fprintf(stderr, "Send to client failed\n");
                ret = ERROR;
            }
            else {
                /* Log successful delivery */
                printf("Quote delivered to user=%s quote_id=%u bytes=%zd\n",
                            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), sent_len);
            }
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
                rfc865Description(0);
                return ret;
            case '?':
            default:
                printHelp(argv[0]);
                return ERROR;
        }
    }

    ret = udpServer();
    if (ret != SUCCESS) {
        fprintf(stderr, "UDP Server encountered an error and is exiting.\n");
    }
    else {
        printf("UDP Server exited successfully.\n");
    }

    return ret;
}
