#pragma once
#ifndef HAND_H
#define HAND_H

#include "rank.h"
#include "suit.h"
#include "Card.h"
#include <algorithm>

class Player {
private:
	int books;
	std::vector <Card *> hand;
public:
	Player():books(0) {}
	int getBookNum() { return books; }

	void sortHand();
	Card * makePlay(Card * playedCard, std::vector <Card*> &table);
	bool checkPlay(Card * playedCard, std::vector <Card*> &table);
	void randomDeal(std::vector <Card*> &deck);
	void displayHand();
	Card * checkCard(const char * card);
	std::vector <Card *>& getHand();
	void setBookNum(int book) { books = book; }

};

#endif
