#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <algorithm>


class Deck{
private:
	
	
public:
	std::vector <Card> deck;
	static std::vector <Card> table;
	
	Deck(){
	for(int suit = (Card::Suit)0; suit <= (Card::Suit)4; suit++){
		//begin inner loop for cardinal value 
		for(int rank = (Card::Rank)0; rank <= (Card::Suit)13; rank++){
			//omit/skip 2 of diamonds and 2 of hearts
			if((rank == Card::TWO) && ((suit == Card::DIAMONDS) || (suit == Card::HEARTS)))
				continue;
			//add cards of current suit and rank from enum to deck
			deck.push_back(Card((Card::Suit)suit, (Card::Rank)rank));
		}
	}
	//add big and little Jokers
	deck.push_back(Card(Card::SPADES, Card::LJ));
	deck.push_back(Card(Card::SPADES, Card::BJ));
	}	
	
	void randomDeal();
	void drawDeal();

};

#endif