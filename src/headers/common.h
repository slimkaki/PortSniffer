// Common libraries to be imported
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

// Socket libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Threading library
#include <pthread.h>

/* Colors on stdout header file */
#include "colors.h"

/* Global thread struct */

struct ThreadParams {
    char *ip;
    int port;
};

/* Global variables */
#define SA struct sockaddr
#define TIMEOUT 10 // seconds
#define MAX_PORTS 65535

/* Sockets buffers length */
#define BUFFERLEN 4096

/* Declaring common functions*/

int setupSocket(char *IP, int port);

void err_n_die(char *msg[]) {fprintf(stderr, "\033[0;31m%s\n\033[0m", *msg); free(msg); exit(1);};

void welcome() {
    printf("=================================================================\n");
    boldBlue(); printf("\tWelcome to the Port-Sniffer");
    reset(); printf(" | ");
    boldRed(); printf("ポートスニファー\n");
    boldGreen(); printf("\t\t\t--made by slimkaki\n");
    reset();
    printf("=================================================================\n\n");
}