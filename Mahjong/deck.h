#pragma once

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
using namespace std;

class Deck
{
public: 
	Deck();
	void print_deck();
	void shuffle();
	bool check_size();
	void deal(vector<pair<int, string>> &player, vector<pair<int, string>> &cpu1, vector<pair<int, string>> &cpu2,
		vector<pair<int, string>> &cpu3);
	pair<int, string> draw_tile(vector<pair<int, string>> &hand);
	bool is_empty();
	
private:
	vector<pair<int, string>> tiles;
};

#endif // !
