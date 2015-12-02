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
int sendMessage(const char* message);
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
	//addr.sin_addr.s_addr = inet_addr("10.20.123.173"); //Server IP
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
	sendMessage("Connected");

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
	Player player = Player();
	bool isPlayer1 = false;
	bool isYourTurn = false;
	bool isRoundOne = true;
	std::string delimiter = " ";
	//size of string
	size_t pos = 0;
	//Line in file as a string
	std::string line;
	//string of part
	std::string part;
	//Deck as a string
	std::string deckString = "";

	std::string playerNum = std::string(recvbuf);

	//If Player 1...
	if (playerNum == "0")
	{
		cout << endl << " Start Player 1" << endl;
		isPlayer1 = true;
		//Create hand for Player
		player.randomDeal(deck.getDeck());

		std::string deckString = "";
		for (int i = 0; i < (int)deck.getDeck().size(); ++i)
		{
			deckString += deck.getDeck()[i]->cardAsString() + " ";
		}
		sendMessage(deckString.c_str());
		recieveMessage();
	} // end if
	else
	{
		cout << endl << " Start Player 2" << endl;
		//Clear Deck
		deck.getDeck().clear();

		//Get Deck from Player 1 
		sendMessage("GetDeck");
		recieveMessage();
		line = std::string(recvbuf);
		for (int i = 0; i < 13; ++i)
		{
			if ((pos = line.find(delimiter)) != std::string::npos)
			{
				part = line.substr(0, pos);
				deck.getDeck().push_back(player.checkCard(part.c_str()));
				line.erase(0, pos + delimiter.length());
			}
		} // end for
		player.randomDeal(deck.getDeck());
		
	} // end else
	while (true)
	{
		if (player.getHand().size() == 0)
		{
			break;
		}
		
		if (!isPlayer1 && isRoundOne)
		{
			//Wait for Player 1
			puts("\n\n Waiting for opponent...");
			recieveMessage();
			deck.getTable().clear();
			line = std::string(recvbuf);
			Card * card = player.checkCard(line.c_str());
			if (card != NULL)
			{
				deck.getTable().push_back(card);
				cout << deck.getTable().back()->displayCard();
			}
			
		}
		else if(!isRoundOne)
		{
			puts("\n\n Waiting for opponent...");
			recieveMessage();
			//Wait for Player's turn
			deck.getTable().clear();
			
			line = std::string(recvbuf);
			if (line == "BOOK")
			{
				cout << endl << " You won that round" << endl;
				player.setBookNum(player.getBookNum() + 1);
				cout << endl << " Current books: " << player.getBookNum() << endl;
			}
			else if (line == "NO_BOOK")
			{
				cout << endl << " You lost that round" << endl;
				cout << endl << " Current books: " << player.getBookNum() << endl;
			}
			else
			{
				Card * card = player.checkCard(line.c_str());
				if (card != NULL)
				{
					deck.getTable().push_back(card);
				}
			}
		}
		isRoundOne = false;

		bool goodCard = false;
		while (!goodCard)
		{
			//Display Table
			if (deck.getTable().size() > 0)
			{
				puts("\n-----------------------------------");
				cout << endl << " Current Table" << endl;
				puts("\n-----------------------------------");
				cout << deck.getTable().back()->displayCard();
			}
			
			puts("\n-----------------------------------");
			puts(" Your Hand");
			puts("-----------------------------------");
			player.displayHand();
			puts("\n-----------------------------------");
			cout << endl << "\n Enter a card to play: ";
			string cardPlayed = "";
			cin >> cardPlayed;
			Card * playerCard;
			if (cardPlayed.length() < 2)
			{
				cout << endl << " Card length invalid. Must be in this format: 'H2'";
			}
			else
			{
				playerCard = player.checkCard(cardPlayed.c_str());
				if (playerCard == NULL)
				{
					cout << endl << " Card invalid. Must be in this format: 'H2'";
				}
				else
				{
					playerCard = player.makePlay(playerCard, deck.getTable());
					if (playerCard != NULL)
					{
						cout << endl << playerCard->displayCard();
						if (deck.getTable().size() > 0 && playerCard->getSuit() != deck.getTable().front()->getSuit())
						{
							if(playerCard->getSuit() != Suit::SPADES)
								cout << endl << " Card suit played does not match suit of card in table";
							else
							{
								goodCard = true;
								if (deck.getTable().size() > 1)
								{
									bool success = player.checkPlay(playerCard, deck.getTable());
									if (success)
									{
										player.setBookNum(player.getBookNum() + 1);
										sendMessage("NO_BOOK");
										cout << endl << endl << " You won that round" << endl;
										cout << endl << " Current books: " << player.getBookNum() << endl;
									}
									else
									{
										sendMessage("BOOK");
										cout << endl << endl << " You lost that round" << endl;
										cout << endl << " Current books: " << player.getBookNum() << endl;
									}
								}
								else
								{
									sendMessage(playerCard->cardAsString().c_str());
								}
							}
						}
						else
						{
							goodCard = true;
							if (deck.getTable().size() > 1)
							{
								bool success = player.checkPlay(playerCard, deck.getTable());
								if (success)
								{
									player.setBookNum(player.getBookNum() + 1);
									sendMessage("NO_BOOK");
									cout << endl << endl << " You won that round" << endl;
									cout << endl << " Current books: " << player.getBookNum() << endl;
								}
								else
								{
									sendMessage("BOOK");
									cout << endl << endl << " You lost that round" << endl;
									cout << endl << " Current books: " << player.getBookNum() << endl;
								}
							}
							else
							{
								sendMessage(playerCard->cardAsString().c_str());
							}
						}
					}
				}

			} // end else
		} // end while
	} // end while

	if (player.getBookNum() > player.getBookNum())
	{
		puts("\n-----------------------------------");
		cout << endl << endl << " Player 1 wins with " << player.getBookNum() << " books" << endl;
		puts("-----------------------------------");
	}
	else
	{
		puts("\n-----------------------------------");
		cout << endl << endl << " Player 2 wins with " << player.getBookNum() << " books" << endl;
		puts("-----------------------------------");
	}

	getline(cin, str);
	getline(cin, str);

	return 0;

} // end main

//Send a message to server
int sendMessage(const char* message)
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
	}
	else if (recieved == 0)
		puts(" Server lost connection");
	else
		printf("WSA ERROR: %d\n", WSAGetLastError());
	return recieved;
} // end recieveMessage
