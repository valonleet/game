#include "Card.h"

GCard::GCard()
{

}

GCard::GCard(std::string name, std::string description, Rarity rarity, Series series, Type type, int value, Color color)
{
	this->name = name;
	this->description = description;
	this->rarity = rarity;
	this->series = series;
	this->type = type;
	this->value = value;
	this->color = color;
}

std::ifstream& operator>>(std::ifstream& lhs, Card c)
{
	return lhs;
}
