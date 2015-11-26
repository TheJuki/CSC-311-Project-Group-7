#include "player.h"

using namespace std;

void Player::sortHand()
{
	std::sort(hand.begin(), hand.end(), [](Card * card1, Card * card2)
	{ return card1->getRank() < card2->getRank() && card1->getSuit() < card2->getSuit(); }
	);
}

Card * Player::makePlay(Suit playedSuit, Rank playedRank, std::vector <Card*> table) {

	Card * playedCard = new Card(playedSuit, playedRank);
	std::vector<Card *>::iterator cardIt;
	cardIt = find(hand.begin(), hand.end(), playedCard);
	if (cardIt == hand.end())
	{
		cout << "Card not in hand";
	}
	else {

		table.push_back(playedCard);

		hand.erase(cardIt);
		hand.shrink_to_fit();

		checkPlay(playedCard, table);

		return playedCard;
	}
	return playedCard;
}

bool Player::checkPlay(Card * playedCard, std::vector <Card*> table) {

	Card * leadCard = table.front();
	std::vector<Card *>::iterator cardIt;
	bool renege = ((playedCard->getSuit() != leadCard->getSuit()) &&
		(find(hand.begin(), hand.end(), playedCard) != hand.end()));
	//check to see if card is thrown off
	if ((leadCard->getSuit() != playedCard->getSuit()) && (playedCard->getSuit() != Suit::SPADES))
		return leadCard->getSuit() < playedCard->getSuit();

	//check for cutting 
	if (playedCard->getSuit() == Suit::SPADES)
		return playedCard->getSuit() < leadCard->getSuit();

	//check to see if renege
	if (renege) {
		books = books - 2;
	}
	return false;

}

void Player::randomDeal(std::vector <Card*> deck) {

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