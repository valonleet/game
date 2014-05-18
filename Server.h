#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <sqlite3.h>

#include "Player.h"
#include "Card.h"

class Server
{
public:
	Server();

	static const int PORT = 8787;

	static const std::string DB_STRING;
	static const std::string CARD_TABLE;
	static const std::string PLAYER_TABLE;

	static void first_run();

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
	static int callback_card(void *NotUsed, int argc, char **argv, char **azColName);
	static int callback_player(void *NotUsed, int argc, char **argv, char **azColName);
	static int callback_gcard(void *NotUsed, int argc, char **argv, char **azColName);

	static bool add_card_db(Card);
	static Card get_card_db(std::string);

	static bool add_gcard_db(GCard);
	static GCard get_gcard_db(std::string);
	static bool update_gcard_db(GCard);
	static bool delete_gcard_db(std::string);

	static bool add_account_db(std::string, std::string, std::string);
	static bool update_account_db(std::string, std::string, std::string);

	static bool add_player_db(Player);
	static Player get_player_db(std::string, std::string);
	static bool update_player_db(Player);
	static bool delete_player_db(std::string);
};

#endif