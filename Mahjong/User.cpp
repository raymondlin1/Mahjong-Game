#include "stdafx.h"
#include "User.h"
#include <iostream>

int CPU_BEFORE_PLAYER = 3;

pair<int, string> User::throw_tile()
{
	cout << "Please enter a tile to throw out" << endl;
	string thrown;
	bool valid_input = false;
	pair<int, string> tile;

	while (!valid_input)
	{
		getline(cin, thrown);
		if (thrown.length() < 4)
		{
			cout << "Please enter a valid tile" << endl;
			continue;
		}


		//check if it's a bonus tile
		if (thrown == "West" || thrown == "East" || thrown == "North" || thrown == "South"
			|| thrown == "Flower 1" || thrown == "Flower 2" || thrown == "Flower 3" || thrown == "Flower 4"
			|| thrown == "Red Middle" || thrown == "Green Good Luck" || thrown == "White Board")
		{
			tile.first = 0;
			tile.second = thrown;
		}
		//check if it's a suite tile
		else if (isdigit(thrown[0]))
		{
			tile.first = thrown[0] - 48; 
			string sub_string = thrown.substr(2, thrown.length());
			if (sub_string == "Bamboos" || sub_string == "Characters" || sub_string == "Circles")
			{
				tile.second = sub_string;
			}
		}
		else
		{
			cout << "Please enter a valid tile" << endl;
			continue;
		}

		//check if the tile is in the user's hand
		if (!this->is_in_hand(tile))
		{
			cout << "Please enter a valid tile" << endl;
		}
		else
			valid_input = true;
	}
	
	vector<pair<int, string>>::iterator it = hand.begin();
	while (it != hand.end())
	{
		if((*it).first == tile.first && (*it).second == tile.second)
			break;
		it++;
	}

	cout << "You threw out a ";
	if (tile.first == 0)
		cout << tile.second << endl;
	else
		cout << tile.first << " of " << tile.second << endl;
	hand.erase(it);

	return tile;
}

bool User::has_combo(pair<int, string> tile, int turn)
{
	//check for triple - "pong"
	for (int i = 0; i < hand.size() - 1; i++)
	{
		if (hand[i] == hand[i + 1] && hand[i] == tile)
			return true;
	}

	//check for up = "shang"
	if (turn == CPU_BEFORE_PLAYER)
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
						return true;
				}
				//if missing middle tile
				else if (abs(first_num - second_num) == 2)
				{
					if (first_num == tile.first - 1 && second_num == tile.first + 1)
						return true;
				}
			}

		}
	}

	return false;
}

bool User::has_combo(pair<int, string> tile, int turn, bool taken)
{
	//check for triple - "pong"
	for (int i = 0; i < hand.size() - 1; i++)
	{
		if (hand[i] == hand[i + 1] && hand[i] == tile)
		{
			if (taken)
			{
				erase_from_hand(tile, tile);
				vector<pair<int, string>> combo;
				combo.push_back(tile);
				combo.push_back(tile);
				combo.push_back(tile);
				combos.push_back(combo);
			}
			return true;
		}
	}

	//check for up = "shang"
	if (turn == CPU_BEFORE_PLAYER)
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
						if (taken)
						{
							vector<pair<int, string>> combo;
							combo.push_back(hand[i]);
							combo.push_back(hand[i + 1]);
							combo.push_back(tile);
							combos.push_back(combo);
							erase_from_hand(hand[i], hand[i + 1]);
						}
						return true;
					}
				}
				//if missing middle tile
				else if (abs(first_num - second_num) == 2)
				{
					if (first_num == tile.first - 1 && second_num == tile.first + 1)
					{
						if (taken)
						{
							vector<pair<int, string>> combo;
							combo.push_back(hand[i]);
							combo.push_back(hand[i + 1]);
							combo.push_back(tile);
							combos.push_back(combo);
							erase_from_hand(hand[i], hand[i + 1]);
						}
						return true;
					}
				}
			}

		}
	}

	return false;
}