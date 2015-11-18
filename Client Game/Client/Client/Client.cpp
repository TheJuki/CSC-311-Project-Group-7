/*
File       : Client.cpp
Program    : CSC 311 Project
Due Date   : November 2015
Authors    : Justin Kirk,
			 Richard McIlwain,
			 Jesse Bryant,
			 Arlando Boykin,
			 Alan Bodiford
Description: Code for CSC 311 Spades Project 
			 Client
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h> 
#include <iostream>
#include <string>

//Prototypes
int sendMessage(char* message);
int recieveMessage();

using namespace std;

#pragma comment(lib, "ws2_32.lib")  

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8888"

SOCKET ServerSocket = INVALID_SOCKET;

char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

string str;


int main() {
	// create WSADATA object
	WSADATA wsaData;

	int iResult;

	//Header
	std::cout << "*****************************************************************" << std::endl
		<< "*                         Spades Client                         *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*          Justin Kirk, Richard McIlwain, Jesse Bryant          *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*               Arlando Boykin, Alan Bodiford                   *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*                    CSC 311 Spades Project                     *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "\n\n";

	puts(" Starting Spades Client V1.0");
	puts("-----------------------------------");

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	puts(" Winsock Initialized");

	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Create a SOCKET for connecting to server
	if (ServerSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());

		WSACleanup();
		return 1;
	}

	printf(" Client SOCKET created\n");

	// Address Info
	SOCKADDR_IN addr;
	//addr.sin_addr.s_addr = inet_addr("192.168.1.135"); //Server IP
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost IP
	addr.sin_family = AF_INET; //IPv4
	addr.sin_port = htons(8888); //Port

	//Connect to Spades Server
	if (connect(ServerSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		puts("\n Server not running");
		cout << "\n Press Enter to Exit: ";
		getline(cin, str);
		return 1;
	}
	puts("\n Connected to Spades Server");
	cout << "\n Press Enter to Continue: ";
	getline(cin, str);

	//Start sending/recieving messages
	sendMessage(" I connected to you server!\n");
	recieveMessage();
	cout << "\n Press Enter to Continue: ";
	getline(cin, str);
	sendMessage(" I would like to set up a game!\n");
	recieveMessage();
	cout << "\n Press Enter to Continue: ";
	getline(cin, str);
	sendMessage(" Card 22\n");
	recieveMessage();

	puts("\n Done sending messages");
	cout << "\n Press Enter to Exit: ";
	getline(cin, str);

	return 0;

} // end main

//Send a message to server
int sendMessage(char* message)
{
	int sent = send(ServerSocket, message, recvbuflen, 0);
	if (sent == 0)
		puts(" Server lost connection");
	return sent;
} // end sendMessage

//Recieve response from server
int recieveMessage()
{
	int recieved = recv(ServerSocket, recvbuf, recvbuflen, 0);
	if (recieved > 0) {
		recvbuf[recieved - 1] = '\0';
		puts(recvbuf);
	}
	else if (recieved == 0)
		puts(" Server lost connection");
	else
		printf("WSA ERROR: %d\n", WSAGetLastError());
	return recieved;
} // end recieveMessage
