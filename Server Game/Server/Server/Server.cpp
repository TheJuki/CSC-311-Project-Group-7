/*
File       : Server.cpp
Program    : CSC 311 Project
Due Date   : November 2015
Authors    : Justin Kirk,
			 Richard McIlwain,
			 Jesse Bryant,
			 Arlando Boykin,
			 Alan Bodiford
Description: Code for CSC 311 Spades Project
			 Server

*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <sstream>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

	int main()
	{
		WSADATA wsa;
		SOCKET master, new_socket, client_socket[2], s;
		struct sockaddr_in server, address;
		int max_clients = 2, activity, addrlen, i, valread;
		char *message = "Connected \r\n";

		//Header
		std::cout << "*****************************************************************" << std::endl
			<< "*                         Spades Server                         *" << std::endl
			<< "*****************************************************************" << std::endl
			<< "*          Justin Kirk, Richard McIlwain, Jesse Bryant          *" << std::endl
			<< "*****************************************************************" << std::endl
			<< "*               Arlando Boykin, Alan Bodiford                   *" << std::endl
			<< "*****************************************************************" << std::endl
			<< "*                    CSC 311 Spades Project                     *" << std::endl
			<< "*****************************************************************" << std::endl
			<< "\n\n";

		puts(" Starting Spades Server V1.0");
		puts("-----------------------------------");

		//Buffer
		int MAXRECV = 1024;
		//Set of socket descriptors
		fd_set readfds;
		//Recieve Buffer
		char *buffer;
		buffer = (char*)malloc((MAXRECV + 1) * sizeof(char));

		for (i = 0; i < max_clients; i++)
		{
			client_socket[i] = 0;
		} // end for

		printf("\n Initialising Winsock...");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("Failed. Error Code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		} // end if

		printf("Initialised.\n");

		//Create a socket
		if ((master = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			printf(" Could not create socket : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		} // end if

		printf(" Socket created.\n");

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET; //IPv4
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(8888); //Port

		//Bind
		if (bind(master, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printf(" Bind failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		} // end if

		puts(" Bind done");

		//Listen to incoming connections
		listen(master, 3);

		//Accept and incoming connection
		puts(" Waiting for a client to join...");

		addrlen = sizeof(struct sockaddr_in);

		//Forever loop...
		while (TRUE)
		{
			//Clear the socket fd set
			FD_ZERO(&readfds);

			//Add master socket to fd set
			FD_SET(master, &readfds);

			//Add child sockets to fd set
			for (i = 0; i < max_clients; i++)
			{
				s = client_socket[i];
				if (s > 0)
				{
					FD_SET(s, &readfds);
				} // end if
			} // end for

			//wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
			activity = select(0, &readfds, NULL, NULL, NULL);

			if (activity == SOCKET_ERROR)
			{
				printf(" Select call failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			} // end if

			//Master socket error check
			if (FD_ISSET(master, &readfds))
			{
				if ((new_socket = accept(master, (struct sockaddr *)&address, (int *)&addrlen))<0)
				{
					perror(" Accept");
					exit(EXIT_FAILURE);
				} // end if

				//inform user of socket number - used in send and receive commands
				printf("\n New client: IP: %s:%d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

				puts(" Client reached\n");

				//Add new client socket
				for (i = 0; i < max_clients; i++)
				{
					if (client_socket[i] == 0)
					{
						client_socket[i] = new_socket;
						//Send connected!
						std::stringstream strs;
						strs << i;
						std::string temp = strs.str();
						const char* clientNum = temp.c_str();
						if (send(new_socket, clientNum, strlen(clientNum), 0) != strlen(clientNum))
						{
							perror(" Send failed");
						} // end if
						break;
					} // end if
				} // end for
			} // end if

			//for each client...
			for (i = 0; i < max_clients; i++)
			{
				s = client_socket[i];
				//if client presend in read sockets             
				if (FD_ISSET(s, &readfds))
				{
					//Get address
					getpeername(s, (struct sockaddr*)&address, (int*)&addrlen);

					valread = recv(s, buffer, MAXRECV, 0);

					if (valread == SOCKET_ERROR)
					{
						int error_code = WSAGetLastError();
						if (error_code == WSAECONNRESET)
						{
							//Client disconnected
							printf(" Client disconnected: %s:%d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

							//Close the socket and mark as 0 in list for reuse
							closesocket(s);
							client_socket[i] = 0;
						} // end if
						else
						{
							printf(" recv failed with error code : %d", error_code);
						} // end else
					} // end if
					if (valread == 0)
					{
						//Client disconnected
						printf(" Client disconnected: %s:%d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

						//Close socket 
						closesocket(s);
						client_socket[i] = 0;
					} // end if
					else
					{
						//add null character
						buffer[valread] = '\0';
						printf(" %s:%d - %s \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port), buffer);
						send(s, buffer, valread, 0);
					} // end else
				} // end if
			} // end for
		} // end while

		//Close and cleanup
		closesocket(s);
		WSACleanup();

		return 0;
	} // end main