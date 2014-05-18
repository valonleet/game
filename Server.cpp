#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include "Split.h"
#include "Server.h"

using std::string;
using std::cerr;
using std::cout;
using std::vector;
using std::string;
using std::list;
const string Server::DB_STRING = "game.sqlite";
const string Server::CARD_TABLE = "cards"; 
const string Server::PLAYER_TABLE = "players";

// callback functions probably have memory leaks
int Server::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	for (int i = 0; i < argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int Server::callback_card(void *NotUsed, int argc, char **argv, char **azColName)
{
	Card* c = new Card;

	c = static_cast<Card*>(NotUsed);

	c->name = argv[1];
	c->description = argv[2];
	c->rarity = (Card::Rarity)atoi(argv[3]);
	c->series = (Card::Series)atoi(argv[4]);
	c->type = (Card::Type)atoi(argv[5]);

	NotUsed = c;

	return 0;
}

int Server::callback_gcard(void *NotUsed, int argc, char **argv, char **azColName)
{
	GCard* g = new GCard;

	g = static_cast<GCard*>(NotUsed);

	g->name = argv[1];
	g->description = argv[2];
	g->rarity = (Card::Rarity)atoi(argv[3]);
	g->series = (Card::Series)atoi(argv[4]);
	g->type = (Card::Type)atoi(argv[5]);
	g->value = (Card::Type)atoi(argv[6]);
	g->color = (GCard::Color)atoi(argv[7]);

	NotUsed = g;

	return 0;
}

int Server::callback_player(void *NotUsed, int argc, char **argv, char **azColName)
{
	string deck_str;
	string collection_str;
	Player* p = new Player;
	p = static_cast<Player*>(NotUsed);

	p->username = argv[1];

	deck_str = argv[4];

	vector<string> deck_cards = split(deck_str, ';');

	for (vector<string>::size_type i = 0; i < deck_cards.size(); i++)
	{
		if (deck_cards[i] != "")
		{
			cout << "CARD NAME: " << deck_cards[i] << std::endl;
			p->deck[i] = get_card_db(deck_cards[i]);
		}
	}

	collection_str = argv[5];

	vector<string> collection_cards = split(deck_str, ';');

	for (vector<string>::size_type i = 0; i < collection_cards.size(); i++)
	{
		if (collection_cards[i] != "")
		{
			cout << "CARD NAME: " << collection_cards[i] << std::endl;
			p->collection.push_back(&get_card_db(collection_cards[i]));
		}
	}

	p->rating = atoi(argv[6]);
	p->rating = atoi(argv[7]);

	NotUsed = p;

	return 0;
}


void Server::first_run()
{
	// defaults
	string CARD_TABLE = "cards";
	string ACC_TABLE  = "accounts";


	sqlite3* db;
	int conn_result;
	int exec_result;
	char* err_str;

	//create DB
	conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " + DB_STRING;
	}

	// create cards table
	const string card_table_sql = "CREATE TABLE " + CARD_TABLE + " (id INTEGER PRIMARY KEY, name VARCHAR(30) UNIQUE, description VARCHAR(255), rarity INTEGER, series INTEGER, type INTEGER, value INTEGER, color INTEGER);";
	const string acc_table_sql = "CREATE TABLE " + PLAYER_TABLE + " (id INTEGER PRIMARY KEY, username VARCHAR(15) UNIQUE, password VARCHAR(15), email VARCHAR(30) UNIQUE, deck VARCHAR(360), collection VARCHAR(10000), points INTEGER, rating INTEGER, is_online INTEGER);";

	exec_result = sqlite3_exec(db, card_table_sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
	}

	exec_result = sqlite3_exec(db, acc_table_sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
	}

	sqlite3_close(db);
}

bool Server::add_card_db(Card c)
{
	string sql = "INSERT INTO " + CARD_TABLE + " (name, description, rarity, series, type) VALUES('" + c.name + "', '" + c.description + "', " + std::to_string(c.rarity) + ", " + std::to_string(c.series) + ", " + std::to_string(c.type) + ");";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " + DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);

	return true;
}

Card Server::get_card_db(string name)
{
	string sql = "SELECT * FROM " + CARD_TABLE + " WHERE name='" + name + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " << DB_STRING;
	}

	char* err_str;

	Card c;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback_card, &c, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
	}

	sqlite3_close(db);

	return c;
}

bool Server::add_gcard_db(GCard g)
{
	string sql = "INSERT INTO " + CARD_TABLE + " (name, description, rarity, series, type, value, color) VALUES('" + g.name + "', '" + g.description + "', " + std::to_string(g.rarity) + ", " + std::to_string(g.series) + ", " + std::to_string(g.type) + ", " + std::to_string(g.value) + ", " + std::to_string(g.color) + ");";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " + DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);

	return true;
}

GCard Server::get_gcard_db(string name)
{
	string sql = "SELECT * FROM " + CARD_TABLE + " WHERE name='" + name + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " << DB_STRING;
	}

	char* err_str;

	GCard g;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback_gcard, &g, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		sqlite3_close(db);
		delete err_str;
	}

	sqlite3_close(db);

	return g;
}

bool Server::update_gcard_db(GCard g)
{
	string sql = "UPDATE " + CARD_TABLE + " SET name='" + g.name + "', description='" + g.description + "', rarity=" + std::to_string(g.rarity) + ", series=" + std::to_string(g.series) + ", type=" + std::to_string(g.type) + ", value=" + std::to_string(g.value) + ", color=" + std::to_string(g.color) + " WHERE name='" + g.name + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " << DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		sqlite3_close(db);
		delete err_str;
		return false;
	}

	sqlite3_close(db);

	return true;
}

bool Server::delete_gcard_db(std::string name)
{
	string sql = "DELETE FROM " + DB_STRING + " WHERE name='" + name + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database: " << DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		sqlite3_close(db);
		delete err_str;
		return false;
	}

	sqlite3_close(db);

	return true;
}

bool Server::add_account_db(string username, string password, string email)
{
	string sql = "INSERT INTO " + PLAYER_TABLE + " (username, password, email, deck, collection, points, rating) " + "VALUES('" + username + "', '" + password + "', '" + email + "', ';', ';', 2000, 1500);";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database : " << DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);

	return true;
}
bool Server::update_account_db(std::string username, std::string password, std::string email)
{
	string sql = "UPDATE " + PLAYER_TABLE + "SET password='" + password + "', email='" + email + "' WHERE username='" + username + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database : " << DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);

	return true;
}


Player Server::get_player_db(string username, string password)
{
	string sql = "SELECT * FROM " + PLAYER_TABLE + " WHERE username='" + username + "' AND password='" + password + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database : " << DB_STRING;
	}

	char* err_str;
	Player p;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback_player, &p, &err_str);
	cout << "FINNA EXIT SOME CALLBACK SHIT 4 REAL ";

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
	}

	sqlite3_close(db);

	return p;
}

bool Server::update_player_db(Player p)
{
	string deck_str;

	for (vector<Card>::size_type i = 0; i < p.deck.size(); i++)
	{
		deck_str += p.deck[i].name + ";";
	}

	string collection_str;

	for (list<Card*>::const_iterator i = p.collection.begin(); i != p.collection.end(); i++)
	{
		collection_str += (*i)->name + ";";
	}

	string sql = "UPDATE " + PLAYER_TABLE + " SET deck='" + deck_str + ", collection='" + collection_str + "', points=" + std::to_string(p.points) + "', rating=" + std::to_string(p.rating) + " WHERE username='" + p.username + "';";

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database : " << DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);

	return true;
}

bool Server::delete_player_db(std::string username)
{
	string sql = "DELETE FROM " + PLAYER_TABLE + " WHERE username='" + username + ';';

	sqlite3* db;

	int conn_result = sqlite3_open(DB_STRING.c_str(), &db);

	if (conn_result)
	{
		cerr << "cannot open database : " << DB_STRING;
		return false;
	}

	char* err_str;

	int exec_result = sqlite3_exec(db, sql.c_str(), callback, 0, &err_str);

	if (exec_result != SQLITE_OK)
	{
		cerr << err_str;
		delete err_str;
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);

	return true;
}