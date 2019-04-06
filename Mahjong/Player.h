#pragma once


#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

class Player
{
public:
	Player();
	vector<pair<int, string>>& get_hand();
	void sort_hand();
	virtual pair<int, string> throw_tile() = 0;
	virtual bool has_combo(pair<int, string> tile, int turn) = 0;
	void add_tile(pair<int, string> tile);
	bool has_winning_hand();
	bool is_in_hand(pair<int, string> tile);
	vector<pair<int, string>> almost_won();
	void print_combos();
	int get_hand_size();
	void clear_structures();
	void change_balance(double amount);
	double get_balance();
	double calculate_payout(string wind);

	//testing purposes
	void set_hand(vector<pair<int, string>> input);
	void print_hand();

protected:
	void erase_from_hand(pair<int, string> tile_1, pair<int, string> tile_2);
	void fix_non_combo_tiles();
	vector<pair<int, string>> hand;
	vector<vector<pair<int, string>>> combos;
	vector<pair<int, string>> non_combo_tiles;
	vector<pair<int, string>> almost_combo_tiles;
	double balance;
};

#endif