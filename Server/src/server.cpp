#include <iostream>
#include <ws2tcpip.h>

int main()
{
  // Initialize winsock
  WSADATA wsData;
  WORD ver{MAKEWORD(2,2)};
  int wsOk{WSAStartup(ver, &wsData)};

  if (wsOk != 0) {
    std::cerr << "Could not initialize winsock! Returned Error: " << wsOk << ". Quitting." << std::endl;
    return 0;
  }

  // Create a socket

  // Bind an ip address and port to a socket

  // Listen on the socket for a client

  // Accept a connection from a client

  // Close listening socket

  // While loop: Receive and Send data

  // Close the socket

  // Cleanup winsock
} 