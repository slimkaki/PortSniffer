#include "headers/common.h"

typedef struct {
    char *IP;
    int PORT;
    int PORTS[];
} ServerData;

void welcome() {
    printf("=================================================================\n");
    boldBlue(); printf("\tWelcome to the Port-Sniffer");
    reset(); printf(" | ");
    boldRed(); printf("ポートスニファー\n");
    boldGreen(); printf("\t\t\t--made by slimkaki\n");
    reset();
    printf("=================================================================\n\n");
}

int setupSocket(char *IP, int port) {
    /* server socket */
    struct sockaddr_in server;

    /* socket file descriptor */
    int sockfd;

    /* local variables */
    int n, sendbytes;
    int len = sizeof(server);

    char sendline[BUFFERLEN];
    char recvline[BUFFERLEN];

    printf("Trying connection with IP %s on port %d\n\n", IP, port);
    /*
     * Creates a stream socket for the client to comunicate with any IP address
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        char *err_msg = (char *) malloc(strlen(IP)*sizeof(char));
        sprintf(err_msg, "Error on client socket creation");
        err_n_die(&err_msg);
    }
    fprintf(stdout, "Client socket created with fd: %d\n", sockfd);

    bzero(&server, sizeof(server));

    /* Defines the connection properties */
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(IP);
    memset(server.sin_zero, 0x0, 8);

    if (inet_pton(AF_INET, IP, &server.sin_addr) <= 0) {
        char *err_msg = (char *) malloc(strlen(IP)*sizeof(char));
        sprintf(err_msg, "inet_pton error for %s", IP);
        err_n_die(&err_msg);
    }

    /* Tries to connect to the server */
    if (connect(sockfd, (struct sockaddr*) &server, len) < 0) {
        char *err_msg = (char *) malloc(strlen(IP)*sizeof(char));
        sprintf(err_msg, "Can't connect to server of IP '%s'", IP);
        err_n_die(&err_msg);
    }

    /* Receives the presentation message from the server */
    // if ((slen = recv(sockfd, buffer_in, BUFFERLEN, 0)) > 0) {
    //     buffer_in[slen + 1] = '\0';
    //     fprintf(stdout, "Server says: %s\n", buffer_in);
    // }


    // We're connected and checking if there is a http service running on port
    // char *sendline[] = (char *) malloc(20*sizeof(char));
    sprintf(sendline, "GET / HTTP/1.1");
    sendbytes = strlen(sendline); 

    if (write(sockfd, sendline, sendbytes) != sendbytes) {
        char *err_msg = (char *) malloc(strlen(IP)*sizeof(char));
        sprintf(err_msg, "[Socket] Write error.");
        err_n_die(&err_msg);
    }

    memset(recvline, 0, BUFFERLEN);

    printf("Waiting for server answer");
    while ((n = read(sockfd, recvline, BUFFERLEN-1)) > 0) {
        boldBlue();
        printf("Response from server: %s", recvline);
        reset();
        memset(recvline, 0, BUFFERLEN);
    }
    if (n < 0) {
        char *err_msg = (char *) malloc(strlen(IP)*sizeof(char));
        sprintf(err_msg, "[Socket] Read error.");
        err_n_die(&err_msg);
    }

    // Send msg to server
    // send(sockfd, sendline, strlen(sendline), 0);

    /* Receives an answer from the server */
    // slen = recv(sockfd, buffer_in, BUFFERLEN, 0);
    // printf("Server answer: %s\n", buffer_in);

    free(sendline);

    // /* Close the connection whith the server */
    close(sockfd);

    fprintf(stdout, "\nConnection closed\n\n");

    return 0;
}

int main(int argc, char *argv[]) {
    /*
    Arguments:
        -ip: IP address to sniff;
        --ports: Specific ports to be scanned
        -T <number of threads> or --threads <number of threads>: Number of threads to be created;
        -h or --help: Display the help menu;
    */
   // Debugging, delete it later
   //====================================================
    boldYellow();
    printf("argc = %d and argv: \n", argc);
    for (int i = 0; i < argc; i++){
        printf("%s, \n", argv[i]);
    }
    printf("\n");
    reset();
    //====================================================
    welcome();
    ServerData srv;
    int numOfThreads;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            printf("Now looking on: %s and %s\n", argv[i], argv[i+1]);
            // printf("Resultado: strcmp('%s', '%s') = %d\n", argv[i], "--ip", strcmp(argv[i], "--ip"));
            if (strcmp(argv[i], "--ip") == 0) {
                srv.IP = argv[i+1];
                i++;
            } else if (strcmp(argv[i], "--port") == 0) {
                srv.PORT = atoi(argv[i+1]);
                i++;
            } else if (strcmp(argv[i], "-T") ==0 || strcmp(argv[i], "--threads") == 0) {
                numOfThreads = atoi(argv[i+1]);
                i++;
            } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                printf("Usage of the port-sniffer:\n");
                printf("\033[1;31m-T <Integer>\033[0m or \033[1;31m--threads <Integer>\033[0m: Number of threads\n");
                exit(0);
            } else {
                // Unknown argument
                char *argumentString = (char*)malloc(strlen(argv[i])*sizeof(char));
                sprintf(argumentString, "Unknown argument '%s'.", argv[i]);
                err_n_die(&argumentString);
            }
        }
    }
    
    setupSocket(srv.IP, srv.PORT);
    return 0;
}