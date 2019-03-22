#include "stdafx.h"
#include "Cpu.h"
#include <time.h>
#include <iostream>

Cpu::Cpu(string input_name)
{
	name = input_name;
}

pair<int, string> Cpu::throw_tile()
{
	//temp code
	srand(time(0));
	int index = rand() % 13;
	pair<int, string> temp = *(hand.begin() + index);
	hand.erase(hand.begin() + index);

	if (this->name == "cpu_1")
		cout << "CPU 1 threw out a " << temp.first << " of " << temp.second << endl;
	else if (this->name == "cpu_2")
		cout << "CPU 2 threw out a " << temp.first << " of " << temp.second << endl;
	else if (this->name == "cpu_3")
		cout << "CPU 3 threw out a " << temp.first << " of " << temp.second << endl;
	else
		cout << "Error: invalid cpu name" << endl;

	return temp;
}