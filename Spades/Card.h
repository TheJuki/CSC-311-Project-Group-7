#pragma once
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include "rank.h"
#include "suit.h"

class Card
{
private:
	Rank rank;
	Suit suit;
public:


	Card() {}
	Card(Suit cardSuit, Rank cardRank) {
		suit = cardSuit;
		rank = cardRank;
	}
	~Card() {}

	//accessor functions
	Rank getRank() { return rank; }
	Suit getSuit() { return suit; }

	//class functions
	bool matchSuit(Suit suit);
	bool checkPlay(Suit suit, Rank rank);

	std::string displayCard();
};
#endif
