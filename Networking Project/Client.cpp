
#define _WINSOCK_DEPRECATED_NO_WARNINGS

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
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(1);
	}

	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// if connection failed
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");

		WSACleanup();
		exit(1);
	}

	// set address info
	SOCKADDR_IN addr;

	printf("Socket created.\n");

	addr.sin_addr.s_addr = inet_addr("192.168.1.135");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);

	//Connect to remote server
	if (connect(ConnectSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		puts("connect error");
		system("PAUSE");
		return 1;
	}
	puts("connected!");
	system("PAUSE");

	char msg[] = "Player has joined server";
	char buffer[512];
	send(ConnectSocket, msg, sizeof(msg), 0);
	int recieve = recv(ConnectSocket, buffer, 512, 0);
	if (recieve > 0) {
		buffer[recieve] = '\0';
		cout << buffer << endl;

	}
	else if (recieve == 0) {
		cout << "Server lost connection" << endl;



	}
	else {
		cout << "WSA ERROR" << WSAGetLastError() << endl;




	}
}
