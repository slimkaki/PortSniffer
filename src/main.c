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

    int len = sizeof(server);
    int slen;

    /* Receive buffer */
    char buffer_in[LEN];
    /* Send buffer */
    char buffer_out[LEN];

    printf("Trying connection with %s on port %d\n\n", IP, port);
    /*
     * Creates a socket for the client
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on client socket creation:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Client socket created with fd: %d\n", sockfd);


    /* Defines the connection properties */
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(IP);
    memset(server.sin_zero, 0x0, 8);

    /* Tries to connect to the server */
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Can't connect to server");
        return EXIT_FAILURE;
    }

    /* Receives the presentation message from the server */
    if ((slen = recv(sockfd, buffer_in, LEN, 0)) > 0) {
        buffer_in[slen + 1] = '\0';
        fprintf(stdout, "Server says: %s\n", buffer_in);
    }

    /*
    * Commuicate with the server until the exit message come
    */
    while (1) {
        /* Zeroing the buffers */
        memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);

        printf("Say something to the server: ");
        fgets(buffer_out, LEN, stdin);

        /* Sends the read message to the server through the socket */
        send(sockfd, buffer_out, strlen(buffer_out), 0);

        /* Receives an answer from the server */
        slen = recv(sockfd, buffer_in, LEN, 0);
        printf("Server answer: %s\n", buffer_in);

        /* 'bye' message finishes the connection */
        if(strcmp(buffer_in, "bye") == 0)
            break;
    }

    /* Close the connection whith the server */
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
            printf("Resultado: strcmp('%s', '%s') = %d\n", argv[i], "--ip", strcmp(argv[i], "--ip"));
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
            }
        }
    }
    
    setupSocket(srv.IP, srv.PORT);
    return 0;
}

int err_n_die(char *msg[]) {
    fprintf(stderr, "\033[0;31m%s\n\033[0m", msg);
    exit(1);
}