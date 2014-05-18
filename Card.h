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

	enum Color
	{
		green

	};
	enum Meta_Type
	{
		gcard,
		ccard
	};

	Card();

	Card(std::string, std::string, Rarity, Series, Type, int, Color, Meta_Type meta_type);

	std::string name;
	std::string description;
	Rarity rarity;
	Series series;
	Type type;
	int value;
	Color color;
	Meta_Type meta_type;
};

#endif