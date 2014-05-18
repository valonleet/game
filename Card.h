#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
public:
	enum Rarity
	{
		common
	};

	enum Series
	{
		one
	};

	enum Type
	{
		huehue
	};

	std::string name;
	std::string description;
	Rarity rarity;
	Series series;
	Type type;
};

class GCard : public Card
{
public:
	enum Color
	{
		green
	};

	GCard();
	GCard(std::string, std::string, Rarity, Series, Type, int, Color);

	int value;
	Color color;
};

std::ostream& operator<<(std::ostream& lhs, Card c);
std::ifstream& operator>>(std::ifstream& lhs, Card c);

class CCard : Card
{

};

#endif