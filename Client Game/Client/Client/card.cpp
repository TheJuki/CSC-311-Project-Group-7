/*
File       : card.cpp
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

#include "Card.h"
#include <string>

bool Card::matchSuit(Suit suit)
{
	return true;
}
bool Card::checkPlay(Suit suit, Rank rank)
{
	return true;
}

std::string Card::displayCard()
{
	return "| " + cardAsString() +" |";
}

std::string Card::cardAsString()
{
	std::string cardString;
	switch (suit)
	{
	case Suit::DIAMONDS: cardString = "D"; break;
	case Suit::CLUBS: cardString = "C"; break;
	case Suit::HEARTS: cardString = "H"; break;
	case Suit::SPADES: cardString = "S"; break;
	}
	switch (rank)
	{
	case Rank::TWO: cardString += "2"; break;
	case Rank::THREE: cardString += "3"; break;
	case Rank::FOUR: cardString += "4"; break;
	case Rank::FIVE: cardString += "5"; break;
	case Rank::SIX: cardString += "6"; break;
	case Rank::SEVEN: cardString += "7"; break;
	case Rank::EIGHT: cardString += "8"; break;
	case Rank::NINE: cardString += "9"; break;
	case Rank::TEN: cardString += "10"; break;
	case Rank::J: cardString += "J"; break;
	case Rank::Q: cardString += "Q"; break;
	case Rank::K: cardString += "K"; break;
	case Rank::A: cardString += "A"; break;
	case Rank::LJ: cardString += "LJ"; break;
	case Rank::BJ: cardString += "BJ"; break;
	}
	return cardString;
}


