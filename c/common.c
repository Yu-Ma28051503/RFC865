/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * TCP Client, TCP Server, UDP Client, UDP Server code common functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

void initQuoteRandom(void)
{
    static int seeded = 0;
    if (!seeded) {
        seeded = 1;
        unsigned seed = (unsigned)time(NULL) ^ (unsigned)getpid();
        srand(seed);
    }
}

const char *getRandomQuote(void)
{
    initQuoteRandom();
    if (QUOTE_COUNT == 0) return "";
    return QUOTES[rand() % QUOTE_COUNT];
}

void rfc865Discription(int isTcp)
{
    const char description[] = 
        "RFC865: Quote of the Day Protocol\n"
        "https://datatracker.ietf.org/doc/html/rfc865\n"
        "This RFC specifies a standard for the ARPA Internet community.  Hosts on "
        "the ARPA Internet that choose to implement a Quote of the Day Protocol "
        "are expected to adopt and implement this standard.\n\n"
        "A useful debugging and measurement tool is a quote of the day service. "
        "A quote of the day service simply sends a short message without regard "
        "to the input.\n\n";

    const char tcp_description[] =
        "TCP Based Character Generator Service\n"
        "   One quote of the day service is defined as a connection based "
        "   application on TCP.  A server listens for TCP connections on TCP port "
        "   17.  Once a connection is established a short message is sent out the "
        "   connection (and any data received is thrown away).  The service "
        "   closes the connection after sending the quote.\n\n";

    const char udp_description[] = 
        "UDP Based Character Generator Service\n"
        "   Another quote of the day service is defined as a datagram based "
        "   application on UDP.  A server listens for UDP datagrams on UDP port "
        "   17.  When a datagram is received, an answering datagram is sent "
        "   containing a quote (the data in the received datagram is ignored).\n\n";

    const char quote_description[] = 
        "Quote Syntax\n"
        "   There is no specific syntax for the quote.  It is recommended that it "
        "   be limited to the ASCII printing characters, space, carriage return, "
        "   and line feed.  The quote may be just one or up to several lines, but "
        "   it should be less than 512 characters.\n\n";

    printf("%s", description);
    printf("%s", isTcp ? tcp_description : udp_description);
    printf("%s", quote_description);
}

void printHelp(char *program)
{
    printf("Usage: %s [options]\n", program);
    printf("Options:\n");
    printf("  -h, --help          Show this help message and exit\n");
    printf("  -d, --description   Show RFC865 description and exit\n");
    printf("Server uses port: %d\n", SERVER_PORT);
    printf("Client connects to IP: %s, port: %d\n", SERVER_IPv4, SERVER_PORT);
}
