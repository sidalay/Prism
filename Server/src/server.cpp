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
  listen(listening, SOMAXCONN);

  // Accept a connection from a client
  sockaddr_in client;
  int clientSize{sizeof(client)};
  SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

  if (clientSocket == INVALID_SOCKET) {
    std::cerr << "Invalid socket! Quitting" << std::endl;
    return 0;
  }

  char host[NI_MAXHOST];            // client's remote name
  char service[NI_MAXSERV];         // Service (i.e. port) the client is connected on

  ZeroMemory(host, NI_MAXHOST);     // same as memset(host, 0, NI_MAXHOST);
  ZeroMemory(service, NI_MAXSERV);

  if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
    std::cout << host << " connected on port " << service << std::endl;
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
  }

  // Close listening socket
  closesocket(listening);

  // While loop: Receive and Send data
  char buf[4096];

  while (true) {
    ZeroMemory(buf, 4096);

    // Wait for client to send data
    int bytesReceived = recv(clientSocket, buf, 4096, 0);

    if (bytesReceived == SOCKET_ERROR) {
      std::cerr << "Error in recv(). Quitting" << std::endl;
      break;
    }

    if (bytesReceived == 0) {
      std::cout << "Client disconnected" << std::endl;
      break;
    }

    // Echo message back to client
    send(clientSocket, buf, bytesReceived + 1, 0);
  }

  // Close the socket

  // Cleanup winsock
} 