#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
#include <array>
#include <algorithm>
#include <vector>
#include "Card.h"

class Player
{
public:
	static const int DECK_MAX = 12;

	Player();
	Player(std::string, Card[12], std::list<Card>, int, int);
	std::string username;
	std::vector<Card> deck;
	std::list<Card*> collection;	// contains GCards and CCards
	int points;
	int rating;
	bool add_to_collection(Card*);
	bool add_to_deck(Card);
};

#endif