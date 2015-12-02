/*
File       : deck.h
Program    : CSC 311 Project
Due Date   : December 2, 2015
Authors    : Justin Kirk,
Richard McIlwain,
Jesse Bryant,
Arlando Boykin,
Alan Bodiford
Description: Code for CSC 311 Spades Project
Server

*/

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
	int myrandom(int i) { return std::rand() % i; }
	Deck() {
		for (int suit = 0; suit <= 3; suit++) {
			//begin inner loop for cardinal value
			for (int rank = 0; rank <= 12; rank++) {
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
		//Shuffle
		random_shuffle(deck.begin(), deck.end());
	}
	std::vector <Card*>& getTable() { return table; }
	std::vector <Card*>& getDeck() { return deck; }

};

#endif
