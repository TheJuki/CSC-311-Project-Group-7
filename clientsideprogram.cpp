#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h> 
#include <iostream>
#include <string>


using namespace std;

#pragma comment(lib, "ws2_32.lib")  


int main() {
    // create WSADATA object
    WSADATA wsaData;

    
    // Initialize Winsock
   int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }



  

	
    //resolve server address and port 
   


    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// if connection failed
    if (ConnectSocket == INVALID_SOCKET) 
    {
        printf("Unable to connect to server!\n");
        
		
		WSACleanup();
        exit(1);
    }

	// Set the mode of the socket to be nonblocking
    u_long iMode = 1;

    iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
    if (iResult == SOCKET_ERROR)
    {
        printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
        system("PAUSE");
		closesocket(ConnectSocket);
        WSACleanup();
        exit(1);        
    }

	//disable nagle
    char value = 1;

	setsockopt( ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );

  // set address info
   SOCKADDR_IN addr;
   inet_pton(AF_INET, "10.20.121.168", &addr.sin_addr);

	
   addr.sin_port = htons(8888);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.20.121.168");
	
	int ret= connect(ConnectSocket, (SOCKADDR *)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR) {
		cout << "connecting to server failed" << endl;
	    system("PAUSE");
		
		exit(0);
	}

	char msg[] = "Player has joined server";
	char buffer[512];
	send(ConnectSocket, msg, sizeof(msg), 0);
	int recieve = recv(ConnectSocket, buffer, 512, 0);
	if (recieve > 0){
    buffer[recieve] = '\0';
	cout << buffer << endl;
	
	} else if (recieve == 0) { 
		cout << "Server lost connection" << endl;
	   
	
	
	}else {   cout << "WSA ERROR" << WSAGetLastError() <<endl;

	
	
	
	}
	}
