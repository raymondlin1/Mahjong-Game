#pragma once

#ifndef USER_H
#define USER_H

#include "Player.h"

class User: public Player
{
public:
	pair<int, string> throw_tile();
	virtual bool has_combo(pair<int, string> tile, int turn);
	bool has_combo(pair<int, string> tile, int turn, bool taken);

private:
	
};

#endif