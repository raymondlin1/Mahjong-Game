#pragma once

#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "User.h"
#include "Cpu.h"

class Game 
{
public:
	Game();
	void print_hands();
	void print_field();
	void play_game();
	void print_player_hand();
	bool declare_victory(string name);
	void check_combos(pair<int, string> &temp, int &turn);
	void calculate_pay(int turn);
	void print_balances();

private:
	vector<pair<int, string>> field_tiles;
	Deck* deck;
	User* player;
	Cpu* cpu_1;
	Cpu* cpu_2;
	Cpu* cpu_3;
	bool game_over;
	int winner;
	string wind;
	int first_player;
};

#endif