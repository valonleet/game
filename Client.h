#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <SFML/Window.hpp>

#include "Player.h"

class Client 
{
public:
	int PORT;

	Client();

	//
	static Player send_login(std::string, std::string);
	bool set_player(Player);
	void connect();
	void disconnect();


	void play();

private:
	Player player;
};

#endif