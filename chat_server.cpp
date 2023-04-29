#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
  // Create a socket
  int server_sock = socket(AF_INET, SOCK_STREAM, 0);

  // Bind the socket to a port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(8888);
  bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

  // Listen for incoming connections
  listen(server_sock, 5);

  // Accept incoming connections and handle them
  struct sockaddr_in client_addr;
  socklen_t client_addr_size = sizeof(client_addr);
  while (true) {
    int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    std::cout << "Client: " << client_sock << " connected!" << std::endl;
    // Send a welcome message to the client
    std::string message = "Welcome to the server!\n";
    send(client_sock, message.c_str(), message.length(), 0);

    // Close the client socket
    // close(client_sock);
  }

  // Close the server socket
  close(server_sock);

  return 0;
}
