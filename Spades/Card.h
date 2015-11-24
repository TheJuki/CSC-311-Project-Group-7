#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>

class Card
{
private:
	Rank rank;
	Suit suit;
public:
	enum Rank{TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, A, LJ, BJ};
	enum Suit{DIAMONDS, CLUBS, HEARTS, SPADES};

	Card();
	Card(Suit cardSuit, Rank cardRank){
	suit = cardSuit;
	rank = cardRank;
	};
	
	//accessor functions
	Rank getRank()	{ return rank; }
	Suit getSuit()	{ return suit; }
	
	//class functions
	bool matchSuit(Suit suit);
	bool checkPlay(Suit suit, Rank rank);

}
#endif