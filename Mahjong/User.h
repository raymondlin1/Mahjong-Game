#pragma once

#ifndef USER_H
#define USER_H

#include "Player.h"

class User: public Player
{
public:
	pair<int, string> throw_tile();

private:
	
};

#endif