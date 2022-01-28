#include "pipe_networking.h"

int main() {
  int sd = server_setup();
  
  while (1) {
    int from_client = server_connect(sd);
    if(from_client == -1){
      printf("client connection unavailable\n");
      return 0;
    }
    
    int f = fork();
    if (f) {} 
    else { 
      char line[BUFFER_SIZE];

      while (1) { // Prompt client for input
        if (read(from_client, line, sizeof(line))==0) {
          int err = close(from_client);
          if(err == -1){
            printf("unable to read from client\n");
          }
          break;
        }
        
        for(int i=0; i<strlen(line); i++) line[i] = tolower(line[i]);
        
        int err = write(from_client, line, sizeof(line)); // send data to client
        if(err == -1){
          printf("unable to write to client\n");
          return 0;
        }
      }
    }
  }
}
