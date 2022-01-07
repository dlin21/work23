#include "pipe_networking.h"


int main() {
    char line[BUFFER_SIZE];

    int sd = client_connect();

    while (1) {
        // Prompts user for input
        printf("Relay Message to Server: ");
        fgets(line, BUFFER_SIZE, stdin);

        write(sd, line, sizeof(line)); // send data to server
        read(sd, line, sizeof(line)); // reads processed data from server
        printf("Response From Server: %s\n", line); // displays processed data to server
    }
}

