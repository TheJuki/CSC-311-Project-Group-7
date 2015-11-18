/*
File       : Server.cpp
Program    : CSC 311 Project
Due Date   : November 2015
Author     : Justin Kirk,
Richard McIlwain,
Jesse Bryant,
Arlando Boykin,
Alan Bodiford
Description: Code for CSC 311 Spades Project
			 Server
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8888"

int main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	//Header
	std::cout << "*****************************************************************" << std::endl
		<< "*                         Spades Server                         *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "* Richard McIlwain, Jesse Bryant, Arlando Boykin, Alan Bodiford *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*                    CSC 311 Spades Project                     *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "\n\n";

	puts(" Starting Spades Server V1.0");
	puts("-----------------------------------");

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	puts(" Winsock Initialized");

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	puts(" Server address and port Initialized");

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	puts(" Server SOCKET created");

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	puts(" TCP listening socket setup");

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	

	puts(" Listening for a connection...");

	// Accept a client socket
	while ((ClientSocket = accept(ListenSocket, NULL, NULL)) != INVALID_SOCKET)
	{
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		puts("\n Client accepted: ");

		int len = sizeof(struct sockaddr);
		struct sockaddr_in sockAddr;
		getsockname(ClientSocket, (struct sockaddr *) &sockAddr, &len);
		fprintf(stderr, " %s:%d\n", inet_ntoa(sockAddr.sin_addr),
			ntohs(sockAddr.sin_port));

		// No longer need server socket
		closesocket(ListenSocket);

		// Receive until the peer shuts down the connection
		do {
			puts("\n Waiting for a message...\n");
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				recvbuf[iResult-1] = '\0';
				puts(recvbuf);

				char *message = " I recieved your message client!\n";
				send(ClientSocket, message, recvbuflen, 0);
			}
			else if (iResult == 0)
				puts(" Client lost connection");
			else
				puts(" WSA ERROR" + WSAGetLastError());

		} while (iResult > 0);

		// Shutdown the connection after client quits
		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf(" shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
		puts("\n Client disconnected");
		
		//Ready to accept another client
		puts("\n Restarting server...");

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		puts(" Server address and port Initialized");

		// Create a SOCKET for connecting to server
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}

		puts(" Server SOCKET created");

		// Setup the TCP listening socket
		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		puts(" TCP listening socket setup");

		freeaddrinfo(result);

		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		puts(" Listening for a connection...");
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}