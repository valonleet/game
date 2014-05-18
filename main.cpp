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

		p.add_to_collection(Server::get_card_db("test1"));
		p.add_to_collection(Server::get_card_db("test2"));
		p.add_to_collection(Server::get_card_db("test3"));

		p.add_to_deck(Server::get_card_db("test4"));
		p.add_to_deck(Server::get_card_db("test5"));
		p.add_to_deck(Server::get_card_db("test6"));

		p.print_collection();

		p.print_deck();

	}
	else
	{
		std::cerr << "invalid login";
		return -1;
	}

	char c;
	cin >> c;

	/*//Client localClient;
	/*
	//send username to server, check if account is in accounts table
	if (localClient.set_player(Client::send_login(username, password)))
	{
		// the login was6 successfull display a menu
	}
	else 
	{
		cout << "sorry invalid username or password";
	}*/

	/*RenderWindow main_window(VideoMode(800, 600), "My window");
	main_window.setFramerateLimit(60);

	string str;
	sf::String text;
	
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
	}*/


	//if so then 

	return 0;
}