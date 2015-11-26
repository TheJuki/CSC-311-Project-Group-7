#include <iostream>
#include <string>
#include "Card.h"
#include "deck.h"
#include "player.h"
#include <ctime>

using namespace std;

int main()
{
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
