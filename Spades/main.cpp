#include <iostream>
#include <string>

#include "Card.h"
#include "deck.h"
#include "player.h"

using namespace std;

int main()
{
    cout << "Spades Game loaded!" << endl;
	

	//Create Deck
	Deck deck = Deck();

	//Create Player
	Player player1 = Player();

	//Create hand for Player
	player1.randomDeal(deck.getDeck());

	player1.displayHand();

	string str;
	getline(cin, str);

    return 0;
}
