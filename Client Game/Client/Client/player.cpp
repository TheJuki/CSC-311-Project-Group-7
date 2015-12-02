/*
File       : player.cpp
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

#include "player.h"

using namespace std;

void Player::sortHand()
{
	std::sort(hand.begin(), hand.end(), [](Card * card1, Card * card2)
	{ return card1->getRank() < card2->getRank() && card1->getSuit() < card2->getSuit(); }
	);
}

Card * Player::makePlay(Card * playedCard, std::vector <Card*> &table) {

	bool foundIt = false;
	int cardLoc = 0;
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->getRank() == playedCard->getRank() &&
			hand[i]->getSuit() == playedCard->getSuit())
		{
			foundIt = true; 
			cardLoc = i;
			break;
		}
	}
	if (!foundIt)
	{
		cout << " Card not in hand";
		return NULL;
	}
	else {
		if (table.size() > 0 && playedCard->getSuit() == table.front()->getSuit())
		{
			table.push_back(playedCard);
			hand.erase(hand.begin() + cardLoc);
			hand.shrink_to_fit();
		}
		else if (table.size() > 0 && playedCard->getSuit() == Suit::SPADES)
		{
			table.push_back(playedCard);
			hand.erase(hand.begin() + cardLoc);
			hand.shrink_to_fit();
		}
		else if (table.size() == 0)
		{
			hand.erase(hand.begin() + cardLoc);
			hand.shrink_to_fit();
		}

		return playedCard;
	}
	return playedCard;
}

bool Player::checkPlay(Card * playedCard, std::vector <Card*> &table) {

	Card * leadCard = table.front();
	bool foundIt = false;
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i]->getRank() == playedCard->getRank() &&
			table[i]->getSuit() == playedCard->getSuit())
			foundIt = true;
	}
	
	//check to see if card is thrown off
	if (leadCard->getSuit() == playedCard->getSuit())
		return leadCard->getRank() < playedCard->getRank();

	//check for cutting 
	if (playedCard->getSuit() == Suit::SPADES)
		return true;

	return false;

}

void Player::randomDeal(std::vector <Card*> &deck) {

	for (int i = 0; i < 13; ++i)
	{
		Player::hand.push_back(deck.at(deck.size() - 1));
		deck.pop_back();
	}
}

void Player::displayHand() {

	for (int i = 0; i < (int)hand.size(); ++i)
	{
		string cardString = hand[i]->displayCard();
		cout << cardString.c_str();
		
	}
}

Card * Player::checkCard(const char * card) {

	int cardSuit = -1;
	int cardRank = -1;

	switch (card[0])
	{
		case 'D':cardSuit = (int)Suit::DIAMONDS; break;
		case 'C':cardSuit = (int)Suit::CLUBS; break;
		case 'H':cardSuit = (int)Suit::HEARTS; break;
		case 'S':cardSuit = (int)Suit::SPADES; break;
	}
	switch (card[1])
	{
		case '2':cardRank = (int)Rank::TWO; break;
		case '3':cardRank = (int)Rank::THREE; break;
		case '4':cardRank = (int)Rank::FOUR; break;
		case '5':cardRank = (int)Rank::FIVE; break;
		case '6':cardRank = (int)Rank::SIX; break;
		case '7':cardRank = (int)Rank::SEVEN; break;
		case '8':cardRank = (int)Rank::EIGHT; break;
		case '9':cardRank = (int)Rank::NINE; break;
		case '1':cardRank = (int)Rank::TEN; break;
		case 'J':cardRank = (int)Rank::J; break;
		case 'Q':cardRank = (int)Rank::Q; break;
		case 'K':cardRank = (int)Rank::K; break;
		case 'A':cardRank = (int)Rank::A; break;
		case 'L':cardRank = (int)Rank::LJ; break;
		case 'B':cardRank = (int)Rank::BJ; break;
	}
	
	if (cardSuit != -1 && cardRank != -1)
		return new Card((Suit)cardSuit, (Rank)cardRank);
	else
		return NULL;
}

std::vector <Card *>& Player::getHand()
{
	return hand;
}