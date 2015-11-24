#include "player.h"


using namespace std;

void Player::sortHand()
{
	std::sort(hand.begin(), hand.end(), [](Card card1, Card card2) 
		{ return card1.getRank() < card2.getRank() && card1.getSuit() < card2.getSuit(); }
	);
}

Card Player::makePlay(Card::Suit playedSuit, Card::Rank playedRank){
	
	Card playedCard = Card(playedSuit, playedRank);

	if(hand.at(find(hand.begin, hand.end, playedCard)) == hand.end())
	{
		cout << "Card not in hand";
	}
	else{

		Deck::table.push_back(playedCard);
		hand.erase(hand.at(find(hand.begin, hand.end, playedCard)));
		hand.shrink_to_fit();

		checkPlay(playedCard);

		return playedCard;
	}
}

bool Player::checkPlay(Player currentPlayer, Card playedCard){
	
	Card leadCard = Deck::table.front();
	bool renege =  ((playedCard.getSuit() != leadCard.getSuit()) && 
					(find(hand.begin(), hand.end(), playedCard.getSuit()) != hand.end()));;
	int playerBooks = currentPlayer.getBookNum();
	//check to see if card is thrown off
	if((leadCard.getSuit() != playedCard.getSuit()) && (playedCard.getSuit() != Card::SPADES))
		return leadCard.getSuit() < playedCard.getSuit();
	
	//check for cutting 
	if(playedCard.getSuit() == Card::SPADES)
		return playedCard.getSuit() < leadCard.getSuit();
	
	//check to see if renege (totally didnt copy this from stackoverflow)
	if(renege){
		playerBooks = playerBooks - 2;
	}

}