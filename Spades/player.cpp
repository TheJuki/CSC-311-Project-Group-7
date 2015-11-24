#include "player.h"

void Player::sortHand()
{
	std::sort(hand.begin(), hand.end(), [](Card * card1, Card * card2)
	{ return card1->getRank() < card2->getRank() && card1->getSuit() < card2->getSuit(); }
	);
}

Card * Player::makePlay(Suit playedSuit, Rank playedRank) {

	Card * playedCard = new Card(playedSuit, playedRank);
	std::vector<Card *>::iterator cardIt;
	cardIt = find(hand.begin(), hand.end(), playedCard);
	if (cardIt == hand.end())
	{
		cout << "Card not in hand";
	}
	else {

		deck.getTable().push_back(playedCard);

		hand.erase(cardIt);
		hand.shrink_to_fit();

		checkPlay(playedCard);

		return playedCard;
	}
	return playedCard;
}

bool Player::checkPlay(Card * playedCard) {

	Card * leadCard = deck.getTable().front();
	std::vector<Card *>::iterator cardIt;
	bool renege = ((playedCard->getSuit() != leadCard->getSuit()) &&
		(find(hand.begin(), hand.end(), playedCard) != hand.end()));
	int playerBooks = this->getBookNum();
	//check to see if card is thrown off
	if ((leadCard->getSuit() != playedCard->getSuit()) && (playedCard->getSuit() != Suit::SPADES))
		return leadCard->getSuit() < playedCard->getSuit();

	//check for cutting 
	if (playedCard->getSuit() == Suit::SPADES)
		return playedCard->getSuit() < leadCard->getSuit();

	//check to see if renege (totally didnt copy this from stackoverflow)
	if (renege) {
		playerBooks = playerBooks - 2;
	}
	return false;

}

void Player::randomDeal() {

	hand.reserve(13);

	random_shuffle(deck.getDeck().begin(), deck.getDeck().end());

	while (hand.back() != NULL)
	{
		Player::hand.push_back(deck.getDeck().at(deck.getDeck().size() - 1));
		deck.getDeck().pop_back();
	}
}