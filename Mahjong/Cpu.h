#pragma once

#ifndef CPU_H
#define CPU_H

#include "Player.h"

class Cpu: public Player
{
public:
	Cpu(string input_name);
	pair<int, string> throw_tile();
	string get_name();
	virtual bool has_combo(pair<int, string> tile, int turn);
	int prev_turn();

private:
	string name;
};

#endif