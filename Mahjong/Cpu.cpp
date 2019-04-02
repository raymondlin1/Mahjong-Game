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
	pair<int, string> temp;

	//throw out a tile in non_combo_tiles or almost_combo_tiles
	this->fix_non_combo_tiles();
	if (non_combo_tiles.empty())
	{
		temp = almost_combo_tiles[almost_combo_tiles.size() - 1];
		almost_combo_tiles.pop_back();
	}
	else
	{
		temp = non_combo_tiles[non_combo_tiles.size() - 1];
		non_combo_tiles.pop_back();
	}
	
	//find it in hand
	for (vector<pair<int, string>>::iterator it = hand.begin(); it != hand.end(); it++)
	{
		if (temp == (*it))
		{
			hand.erase(it);
			break;
		}
	}

	if (this->name == "cpu_1")
		cout << "CPU 1 threw out a ";
	else if (this->name == "cpu_2")
		cout << "CPU 2 threw out a ";
	else if (this->name == "cpu_3")
		cout << "CPU 3 threw out a ";
	else
		cout << "Error: invalid cpu name" << endl;

	if (temp.first == 0)
		cout << temp.second << endl;
	else
		cout << temp.first << " of " << temp.second << endl;

	return temp;
}

string Cpu::get_name()
{
	return name;
}

bool Cpu::has_combo(pair<int, string> tile, int turn)
{
	//check for triple - "pong"
	for (int i = 0; i < hand.size() - 1; i++)
	{
		if (hand[i] == hand[i + 1] && hand[i] == tile)
		{
			erase_from_hand(tile, tile);
			vector<pair<int, string>> combo;
			combo.push_back(tile);
			combo.push_back(tile);
			combo.push_back(tile);
			combos.push_back(combo);
			return true;
		}
	}

	//check for up = "shang"
	if (turn == this->prev_turn())
	{
		for (int i = 0; i < hand.size() - 1; i++)
		{
			int first_num = hand[i].first;
			string first_suite = hand[i].second;
			int second_num = hand[i + 1].first;
			string second_suite = hand[i + 1].second;

			if (first_suite == second_suite && first_suite == tile.second)
			{
				//if two consecutive
				if (abs(first_num - second_num) == 1)
				{
					if (second_num == tile.first - 1 || first_num == tile.first + 1)
					{
						vector<pair<int, string>> combo;
						combo.push_back(hand[i]);
						combo.push_back(hand[i + 1]);
						combo.push_back(tile);
						combos.push_back(combo);
						erase_from_hand(hand[i], hand[i + 1]);
						return true;
					}
				}
				//if missing middle tile
				else if (abs(first_num - second_num) == 2)
				{
					if (first_num == tile.first - 1 && second_num == tile.first + 1)
					{
						vector<pair<int, string>> combo;
						combo.push_back(hand[i]);
						combo.push_back(hand[i + 1]);
						combo.push_back(tile);
						combos.push_back(combo);
						erase_from_hand(hand[i], hand[i + 1]);
						return true;
					}
				}
			}

		}
	}

	return false;
}

int Cpu::prev_turn()
{
	if (this->name == "cpu_1")
		return 0;
	else if (this->name == "cpu_2")
		return 1;
	else if (this->name == "cpu_3")
		return 2;
	else
		exit(1);
}