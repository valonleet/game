#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "Card.h"
#include "Tools.h"

using sf::Event;
using sf::Window;
using sf::VideoMode;
using sf::RenderWindow;
using sf::String;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void)
{
	string username = "lolol";
	string password = "testset";
	string email = "fuck@you";

	cout << "DB First Run..." << endl;
	Server::first_run();
	cout << "Done" << endl;

	/*cout << "Please enter your Username: ";
	cin >> username;

	cout << "Please enter your Password: ";
	cin >> password;

	cout << "Please enter your email: ";
	cin >> email;*/

	//Server::add_account_db(username, password, email);

	Player p = Server::get_player_db(username, password);

	
	if (p.username != "")
	{
		cout << "Login Sucess!" << endl;
		cout << "Welcome " + p.username << endl;

		p.print_collection();

		p.print_deck();

		//Server::update_player_db(p);

		Client localClient;

		RenderWindow main_window(VideoMode(1280, 720, 32), "My window");
		main_window.setFramerateLimit(60);

		string str;
		sf::String text;

		sf::Font arial_font;

		if (!arial_font.loadFromFile("fonts/arial.ttf"))
		{
			std::cerr << "error loading font";
		}

		string menu_options_str[] = { "Play", "Deck", "Collection", "Options" };

		int num_options = sizeof(menu_options_str) / sizeof(string);

		sf::Text* menu_options = new sf::Text[num_options];

		for (int i = 0; i < num_options; i++)
		{
			menu_options[i].setFont(arial_font);
			menu_options[i].setString(menu_options_str[i]);
			menu_options[i].setCharacterSize(20);
			menu_options[i].setColor(sf::Color::Red);
		}

		sf::Text test;

		test.setFont(arial_font);
		test.setString("TEST");
		test.setCharacterSize(24);
		test.setColor(sf::Color::Red);

		while (main_window.isOpen())
		{
			Event event;
			while (main_window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					main_window.close();
					break;

				case Event::TextEntered:
					if (event.text.unicode < 128)
					{
						text += static_cast<char>(event.text.unicode);
						str += static_cast<char>(event.text.unicode);
						std::cout << str << std::endl;
					}
				}

			}

			main_window.clear(sf::Color::Black);

			for (int i = 0; i < num_options; i++)
			{
				main_window.draw(menu_options[i]);
			}

			main_window.display();

		}
	}
	else
	{
		std::cerr << "invalid login";
		return -1;
	}


	//if so then 

	return 0;
}