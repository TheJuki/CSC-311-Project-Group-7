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
#include "Card.h"
#include "deck.h"
#include "player.h"
#include <ctime>

//Prototypes
int sendMessage(char* message);
int recieveMessage();

using namespace std;

#pragma comment(lib, "ws2_32.lib")  

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "8888"

SOCKET ServerSocket = INVALID_SOCKET;

int recvbuflen = DEFAULT_BUFLEN;
char *recvbuf = (char*)malloc((recvbuflen + 1) * sizeof(char));

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
	recieveMessage();
	sendMessage("Got it");

	cout << "\n Press Enter to Start: ";
	getline(cin, str);

	//For Random Shuffle
	srand(time(0));

	//Header
	std::cout << "*****************************************************************" << std::endl
		<< "*                             Spades                            *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*          Justin Kirk, Richard McIlwain, Jesse Bryant          *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*               Arlando Boykin, Alan Bodiford                   *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "*                    CSC 311 Spades Project                     *" << std::endl
		<< "*****************************************************************" << std::endl
		<< "\n";

	puts(" Instructions");
	puts("-----------------------------------");

	std::cout << " Your hand of cards in randomly dealt to you from the deck." << endl;
	std::cout << " The game of two-handed spades is a card game where each player"
		<< endl << " takes turns drawing and discarding cards from a deck until the"
		<< endl << " deck is exhausted. Once both players have a hand of 13 cards,"
		<< endl << " one player plays a card, in which the other must play a card"
		<< endl << " of the same suit. Whichever card is highest wins that round"
		<< endl << " and collects the cards played into a \"book\". The winner of"
		<< endl << " the round then plays his next desired card, and this cycle"
		<< endl << " repeats until both players hands are empty. Whoever has most"
		<< endl << " books at the end of the game wins. Spades, however, are a"
		<< endl << " special suit and \"cuts\", or beats, any suit that it is pitted against." << endl;

	cout << endl << " Press Enter to continue ->";
	string str;
	getline(cin, str);
	cout << endl;

	//Create Deck
	Deck deck = Deck();

	//Create Player
	Player player1 = Player();

	//Create Player
	Player player2 = Player();

	//Create hand for Player
	player1.randomDeal(deck.getDeck());

	//Create hand for Player
	player2.randomDeal(deck.getDeck());

	while (true)
	{
		if (player1.getHand().size() == 0)
		{
			break;
		}
		puts("\n-----------------------------------");
		puts(" Your Hand");
		puts("-----------------------------------");
		player1.displayHand();
		puts("\n-----------------------------------");
		cout << endl << " Enter the card to play: ";
		string cardPlayed = "";
		cin >> cardPlayed;
		Card * playerCard;
		if (cardPlayed.length() < 2)
		{
			cout << endl << " Card length invalid. Must be in this format: 'H2'";
		}
		else
		{
			playerCard = player1.checkCard(cardPlayed.c_str());
			if (playerCard == NULL)
			{
				cout << endl << " Card invalid. Must be in this format: 'H2'";
			}
			else
			{
				playerCard = player1.makePlay(playerCard, deck.getTable());
				if (playerCard != NULL)
				{
					cout << endl << playerCard->displayCard();
				}
			}

		}
	} // end while

	if (player1.getBookNum() > player2.getBookNum())
	{
		puts("\n-----------------------------------");
		cout << endl << endl << " Player 1 wins with " << player1.getBookNum() << " books" << endl;
		puts("-----------------------------------");
	}
	else
	{
		puts("\n-----------------------------------");
		cout << endl << endl << " Player 2 wins with " << player1.getBookNum() << " books" << endl;
		puts("-----------------------------------");
	}

	getline(cin, str);
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
		recvbuf[recieved] = '\0';
		puts(recvbuf);
	}
	else if (recieved == 0)
		puts(" Server lost connection");
	else
		printf("WSA ERROR: %d\n", WSAGetLastError());
	return recieved;
} // end recieveMessage
