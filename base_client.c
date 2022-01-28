#include "pipe_networking.h"

int main() {
    char line[BUFFER_SIZE];
    int sd = client_connect();

    while (1) {
        printf("message: ");
        fgets(line, BUFFER_SIZE, stdin);
        int err = write(sd, line, sizeof(line));
        if(err == -1){
            printf("unable to write to server...\n");
            return 0;
        }
        int err = read(sd, line, sizeof(line));
        if(err == -1){
            printf("unable to read from server...\n");
            return 0;
        }
        printf("response: %s\n", line);
    }
}
