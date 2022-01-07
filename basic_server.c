#include "pipe_networking.h"

int main() {
  int sd = server_setup();
  
  while (1) {
    int from_client = server_connect(sd);
    int f = fork();
       
    if (f) {} 
        
    else { 
      char line[BUFFER_SIZE];

      while (1) { // Prompt client for input
        if (read(from_client, line, sizeof(line))==0) {
          close(from_client);
          break;
        }
        for(int i=0; i<strlen(line); i++) line[i] = tolower(line[i]);
        write(from_client, line, sizeof(line)); // send data to client
      }
  }
  return 0;
}
