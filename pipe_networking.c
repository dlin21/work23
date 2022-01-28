#include "pipe_networking.h"

int server_setup() {
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    int err = getaddrinfo(NULL, "9845", hints, &results);  //Server sets node to NULL
    if(err == -1){
        printf("server: unable to get IP info...\n");
        return -1;
    }
    // create socket
    int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if(sd == -1){
        printf("server: unable to make socket...\n");
        return -1;
    }
    int err = bind(sd, results->ai_addr, results->ai_addrlen);
    if(err == -1){
        printf("server: unable to get bind socket...\n");
        return -1;
    }

    printf("listening...\n");
    int err = listen(sd, 10);
    if(err == -1){
        printf("server: unable to listen...\n");
        return -1;
    }

    free(hints);
    freeaddrinfo(results);

    return sd;
}

int server_connect(int sd) {
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);
    if(client_socket == -1){
        printf("error: %s\n", strerror(errno));
        return -1;
    }
  
    return client_socket;
}

int client_connect() {
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    int err = getaddrinfo("127.0.0.1", "9845", hints, &results);  //Server sets node to NULL
    if(err == -1){
        printf("client: unable to get IP info...\n");
        return -1;
    }
  
    int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if(sd == -1){
        printf("client: unable to make socket...\n");
        return -1;
    }
    int err = connect(sd, results->ai_addr, results->ai_addrlen);;
    if(err == -1){
        printf("client: unable to connect to server...\n");
        return -1;
    }
    
    free(hints);
    freeaddrinfo(results);

    return sd;
}
