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

			if (attr[0] == "gcard")
			{
				GCard g(attr[1], attr[2], (Card::Rarity)atoi(attr[3].c_str()), (Card::Series)atoi(attr[4].c_str()), (Card::Type)atoi(attr[5].c_str()), atoi(attr[6].c_str()), (GCard::Color)atoi(attr[7].c_str()));
				if (Server::add_gcard_db(g))
				{
					std::cout << "Added " + g.name + " to the DB" << std::endl;
				}
				else
				{
					std::cout << "Error adding " + g.name + " to the DB" << std::endl;
				}

			}
			else 
			{
				// implemented later for ccards and what not
			}
		}
	}
	else 
	{
		cerr << "Error opening card file.";
	}
}