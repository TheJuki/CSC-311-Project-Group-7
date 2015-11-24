#ifndef HAND_H
#define HAND_H

#include "deck.h"

class Player{
private:
	int books;
public:
	static std::vector <Card> hand;
	int getBookNum() { return books; }

void sortHand();
Card makePlay(Card::Suit suit, Card::Rank rank);
bool checkPlay(Player currentPlayer, Card playedCard);

}

#endif