#include <iostream>
#include <vector>
#include "Player.h"

using std::string;
using std::list;
using std::cout;
using std::cin;
using std::vector;

Player::Player()
{
	points = 0;
	rating = 0;
}

bool Player::add_to_collection(Card c)
{
	if (collection.size() < 255)
	{
		collection.push_back(c);
		return true;
	}

	return false;
	
}

bool Player::add_to_deck(Card g)
{
	if (deck.size() < DECK_MAX)
	{
		deck.push_back(g);
		return true;
	}

	return false;
}

void Player::print_collection()
{
	for (list<Card>::const_iterator i = collection.begin(); i != collection.end(); i++)
	{
		cout << i->name << ": ";
	}

	cout << std::endl;
}

void Player::print_deck()
{
	for (vector<Card>::const_iterator i = deck.begin(); i != deck.end(); i++)
	{
		cout << i->name << ": ";
	}
	cout << std::endl;
}
