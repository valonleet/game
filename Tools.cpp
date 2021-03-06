#include <fstream>
#include <vector>
#include "Tools.h"
#include "Split.h"
#include "Card.h"
#include "Server.h"

using std::string;
using std::getline;
using std::ifstream;
using std::cerr;
using std::vector;

/* tools for adding cards, packs, accounts, etc */

// inserts cards from a file into the card table
void Tools::create_cards_file(string file_str)
{
	string line;
	ifstream file(file_str);

	if (file.is_open())
	{
		string line;

		while (getline(file, line))
		{
			vector<string> attr = split(line, ';');

			Card g(attr[1], attr[2], (Card::Rarity)atoi(attr[3].c_str()), (Card::Series)atoi(attr[4].c_str()), (Card::Type)atoi(attr[5].c_str()), atoi(attr[6].c_str()), (Card::Color)atoi(attr[7].c_str()), (Card::Meta_Type)atoi(attr[0].c_str()));

			if (Server::add_card_db(g))
			{
				std::cout << "Added " + g.name + " to the DB" << std::endl;
			}
			else
			{
				std::cout << "Error adding " + g.name + " to the DB" << std::endl;
			}
		}
	}
	else 
	{
		cerr << "Error opening card file.";
	}
}