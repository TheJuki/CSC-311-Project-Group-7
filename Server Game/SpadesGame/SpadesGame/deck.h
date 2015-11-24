#ifndef DECK_H
#define DECK_H

using namespace std;

#include "Card.h"
#include <algorithm>


class Deck {
private:
	std::vector <Card*> deck;
	std::vector <Card*> table;

public:

	Deck() {
		for (int suit = 0; suit <= 4; suit++) {
			//begin inner loop for cardinal value
			for (int rank = 0; rank <= 13; rank++) {
				//omit/skip 2 of diamonds and 2 of hearts
				if ((rank == (int)Rank::TWO) && ((suit == (int)Suit::DIAMONDS) || (suit == (int)Suit::HEARTS)))
					continue;
				else
				{
					Card * myCard = new Card((Suit)suit, (Rank)rank);
					deck.push_back(myCard);
				}

			}
		}
		//add big and little Jokers
		Card * lilJoker = new Card(Suit::SPADES, Rank::LJ);
		deck.push_back(lilJoker);
		Card * bigJoker = new Card(Suit::SPADES, Rank::BJ);
		deck.push_back(bigJoker);
	}
	std::vector <Card*> getTable() { return table; }
std::vector <Card*> getDeck() { return deck; }

	void randomDeal();
	void drawDeal();

};

#endif
