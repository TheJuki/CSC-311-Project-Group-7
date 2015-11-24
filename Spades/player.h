#pragma once
#ifndef HAND_H
#define HAND_H

#include "deck.h"
#include "rank.h"
#include "suit.h"

class Player {
private:
	int books;
	Deck deck;
	std::vector <Card *> hand;
public:
	Player()
	{
		deck = Deck();
	}
	int getBookNum() { return books; }

	void sortHand();
	Card * makePlay(Suit suit, Rank rank);
	bool checkPlay(Card * playedCard);
	void randomDeal();

};

#endif
