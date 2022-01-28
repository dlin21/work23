#include "pipe_networking.h"


int main() {
    char line[BUFFER_SIZE];

    int sd = client_connect();

    while (1) {
        // Prompts user for input
        printf("message: ");
        fgets(line, BUFFER_SIZE, stdin);
        int err = write(sd, line, sizeof(line)); // send data to server
        if(err == -1){
            printf("unable to write to server...\n");
            return 0;
        }
        int err = read(sd, line, sizeof(line)); // reads processed data from server
        if(err == -1){
            printf("unable to read from server...\n");
            return 0;
        }
        printf("response: %s\n", line); // displays processed data to server
    }
}
