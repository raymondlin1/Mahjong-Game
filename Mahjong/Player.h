#pragma once


#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

class Player
{
public:
	vector<pair<int, string>>& get_hand();
	void sort_hand();
	virtual pair<int, string> throw_tile() = 0;
	bool has_combo(pair<int, string> tile, int turn);
	void add_tile(pair<int, string> tile);
	bool has_winning_hand();

	//testing purposes
	void set_hand(vector<pair<int, string>> input);
	void print_hand();

protected:
	vector<pair<int, string>> hand;
};

#endif