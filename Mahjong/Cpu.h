#pragma once

#ifndef CPU_H
#define CPU_H

#include "Player.h"

class Cpu: public Player
{
public:
	Cpu(string input_name);
	pair<int, string> throw_tile();

private:
	string name;
};

#endif