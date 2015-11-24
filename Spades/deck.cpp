#include "deck.h"
#include "player.h"

using namespace std;

void Deck::randomDeal(){

	Player::hand.reserve(13);

	random_shuffle(deck.cbegin(), deck.cend());

	while(Player::hand.back == NULL)
	{
		Player::hand.push_back(deck.at(deck.size() - 1));
		deck.pop_back();
	}
}
/*
void Deck::drawDeal(){
	//declaring temp hand here for tesing purposes
	vector <Card> hand (13);
	
	random_shuffle(deck.cbegin(), deck.cend());

	while(hand.back != NULL){
		char userAnswer;
		cout << "Do you want " << deck.at(deck.size() - 1) << " ? (Type Y or N)";
		cin >> userAnswer;


	
	}

}
*/
