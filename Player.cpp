#include "Player.h"

using std::string;
using std::list;

Player::Player()
{
	
}

Player::Player(string username, Card deck[12], list<Card> collection, int points, int rating)
{

}

bool Player::add_to_collection(Card* c)
{
	if (collection.size() < 255)
	{
		collection.push_back(c);
		return true;
	}

	return false;
	
}

bool Player::add_to_deck(Card c)
{
	if (deck.size() < DECK_MAX)
	{
		deck.push_back(c);
		return true;
	}

	return false;
}