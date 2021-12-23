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

// Colors on stdout header file
#include "colors.h"

// Global variables
#define TEST_ADDR "192.168.15.68"
#define TEST_PORT 1337

/* Sockets buffers length */
#define LEN 4096

int err_n_die(char *msg[]);