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
  SOCKET listening{socket(AF_INET, SOCK_STREAM, 0)};

  if (listening == INVALID_SOCKET) {
    std::cerr << "Can not create a socket! Quitting" << std::endl;
    return 0;
  }

  // Bind an ip address and port to a socket
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(54000);
  hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton...
  bind(listening, (sockaddr*)&hint, sizeof(hint));

  // Listen on the socket for a client

  // Accept a connection from a client

  // Close listening socket

  // While loop: Receive and Send data

  // Close the socket

  // Cleanup winsock
} 