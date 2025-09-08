/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 *
 * Common declarations for TCP / UDP client & server
 */

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>   /* for size_t */

/* Return codes */
#define SUCCESS 0
#define ERROR   -1

/* Server defaults */
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 17

/* Buffers */
#define BUFFER_SIZE 512

/* Prototypes */
void rfc865Description(int isTcp);
void printHelp(char *program);

/* Random quote helper (実装は common.c 例を参照) */
const char *getRandomQuote(void);

#endif /* COMMON_H */
