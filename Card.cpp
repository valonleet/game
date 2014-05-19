#include "Card.h"

Card::Card()
{

}

Card::Card(std::string name, std::string description, Rarity rarity, Series series, Type type, int value, Color color, Meta_Type meta_type)
{
	this->name = name;
	this->description = description;
	this->rarity = rarity;
	this->series = series;
	this->type = type;
	this->value = value;
	this->color = color;
	this->meta_type = meta_type;
}
