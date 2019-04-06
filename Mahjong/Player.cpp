#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include <iostream>

void bubble_sort_hand(vector<pair<int, string>> &arr, bool first, int start, int end);
void find_combos(vector<vector<pair<int, string>>> &stack, vector<pair<int, string>> &copy);
bool has_winning_hand_helper(vector<vector<pair<int, string>>> &stack, vector<pair<int, string>> &copy);

vector<pair<int, string>>& Player::get_hand()
{
	return hand;
}

void Player::sort_hand()
{
	//bubble sort the hand by suite
	bubble_sort_hand(hand, false, 0, hand.size());

	//bubble sort the hand by value
	int index = 0;
	int start = 0;
	bool sorted_once = false;
	while (index != hand.size())
	{
		if (index == hand.size() - 1 || hand[index].second != hand[index + 1].second)
		{
			bubble_sort_hand(hand, true, start, index + 1);
			sorted_once = true;
			start = index + 1;
		}
		
		index++;
	}

	//all same suite
	if (!sorted_once)
	{
		bubble_sort_hand(hand, true, 0, hand.size());
	}
}

void bubble_sort_hand(vector<pair<int, string>> &arr, bool first, int start, int end)
{
	bool swapped = true;
	while (swapped == true)
	{
		swapped = false;
		for (int i = start; i < end - 1; i++)
		{
			if (!first)
			{
				if (arr[i + 1].second < arr[i].second)
				{
					pair<int, string> temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
					swapped = true;
				}
			}
			else
			{
				if (arr[i + 1].first < arr[i].first)
				{
					pair<int, string> temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
					swapped = true;
				}
			}
		}
	}
}

void Player::add_tile(pair<int, string> tile)
{
	hand.push_back(tile);
}

bool Player::has_winning_hand()
{
	//since we only run this function whenever a player takes a tile, if their hand size is 1, the acquired tile must be the same as the tile on hand
	if (hand.size() == 1)
		return true;

	vector<pair<int,string>> copy = hand;
	vector<vector<pair<int, string>>> stack;

	//first check for all possible combos
	find_combos(stack, copy);
	if (has_winning_hand_helper(stack, copy))
	{
		return true;
	}
	else
	{
		non_combo_tiles = copy;
		return false;
	}
}

bool has_winning_hand_helper(vector<vector<pair<int, string>>> &stack, vector<pair<int, string>> &copy)
{
	if (copy.size() == 2)
	{
		if (copy[0].first == copy[1].first && copy[0].second == copy[1].second)
		{
			return true;
		}
		else
			return false;
	}

	if (stack.empty())
		return false;

	vector<pair<int, string>> curr_combo = stack.back();
	stack.pop_back();
	int counter = 0;
	//delete the current combo from copy
	for (int i = 0; i < curr_combo.size(); i++)
	{
		for (vector<pair<int, string>>::iterator it = copy.begin(); it != copy.end(); it++)
		{
			if (curr_combo[i] == *it)
			{
				counter++;
				copy.erase(it);
				break;
			}
		}
	}

	//if the combo was not successfully deleted from copy - meaning there are no more combos
	if (counter != 3)
		return false;

	//search for the next combo
	find_combos(stack, copy);

	return has_winning_hand_helper(stack, copy);
}

void find_combos(vector<vector<pair<int, string>>> &stack, vector<pair<int, string>> &copy)
{
	if (copy.size() <= 2)
		return;

	for (int i = 0; i < copy.size() - 2; i++)
	{
		if (copy[i] == copy[i + 1] && copy[i] == copy[i + 2])
		{
			vector<pair<int, string>> temp;
			temp.push_back(copy[i]);
			temp.push_back(copy[i + 1]);
			temp.push_back(copy[i + 2]);
			stack.push_back(temp);
		}
		else if (copy[i].second == copy[i + 1].second && copy[i].first == copy[i + 1].first - 1
			&& copy[i + 1].second == copy[i + 2].second && copy[i + 1].first == copy[i + 2].first - 1)
		{
			vector<pair<int, string>> temp;
			temp.push_back(copy[i]);
			temp.push_back(copy[i + 1]);
			temp.push_back(copy[i + 2]);
			stack.push_back(temp);
		}
	}
}

bool Player::is_in_hand(pair<int, string> tile)
{
	vector<pair<int, string>>::iterator it = hand.begin();
	while (it != hand.end())
	{
		if (tile.first == (*it).first && tile.second == (*it).second)
			return true;
		it++;
	}

	return false;
}

vector<pair<int,string>> Player::almost_won()
{
	vector<pair<int, string>> winning_tiles;
	pair<int, string> tile;

	if (non_combo_tiles.size() == 1 && almost_combo_tiles.empty())
	{
		tile.first = non_combo_tiles[0].first;
		tile.second = non_combo_tiles[0].second;
		winning_tiles.push_back(tile);
	}
	else if (almost_combo_tiles.size() == 4 && non_combo_tiles.empty())
	{
		//two pairs
		if (almost_combo_tiles[0] == almost_combo_tiles[1] && almost_combo_tiles[2] == almost_combo_tiles[3])
		{
			winning_tiles.push_back(almost_combo_tiles[0]);
			winning_tiles.push_back(almost_combo_tiles[2]);
		}
		//first two tiles are pairs
		else if (almost_combo_tiles[0] == almost_combo_tiles[1])
		{
			//if consecutive tiles
			if (almost_combo_tiles[2].first == almost_combo_tiles[3].first - 1)
			{
				//if first tile is 1, push back 3
				if (almost_combo_tiles[2].first == 1)
				{
					tile.first = 3;
					tile.second = almost_combo_tiles[3].second;
					winning_tiles.push_back(tile);
				}
				//if second tile is 9, push back 7
				else if (almost_combo_tiles[3].first == 9)
				{
					tile.first = 7;
					tile.second = almost_combo_tiles[3].second;
					winning_tiles.push_back(tile);
				}
				//if first tile isn't 1 and second tile isn't 9, push back both tiles that belong before and after the consecutive tiles
				else
				{
					tile.first = almost_combo_tiles[2].first - 1;
					tile.second = almost_combo_tiles[2].second;
					winning_tiles.push_back(tile);

					tile.first = almost_combo_tiles[3].first + 1;
					tile.second = almost_combo_tiles[3].second;
					winning_tiles.push_back(tile);
				}
			}
			//if tile missing in between
			else if (almost_combo_tiles[2].first == almost_combo_tiles[3].first - 2)
			{
				tile.first = almost_combo_tiles[2].first + 1;
				tile.second = almost_combo_tiles[2].second;
				winning_tiles.push_back(tile);
			}
		}
		//second two tiles are pairs
		else if (almost_combo_tiles[2] == almost_combo_tiles[3])
		{
			//if consecutive tiles
			if (almost_combo_tiles[0].first == almost_combo_tiles[1].first - 1)
			{
				//if first tile is 1, push back 3
				if (almost_combo_tiles[0].first == 1)
				{
					tile.first = 3;
					tile.second = almost_combo_tiles[0].second;
					winning_tiles.push_back(tile);
				}
				//if second tile is 9, push back 7
				else if (almost_combo_tiles[1].first == 9)
				{
					tile.first = 7;
					tile.second = almost_combo_tiles[1].second;
					winning_tiles.push_back(tile);
				}
				//if first tile isn't 1 and second tile isn't 9, push back both tiles that belong before and after the consecutive tiles
				else
				{
					tile.first = almost_combo_tiles[0].first - 1;
					tile.second = almost_combo_tiles[0].second;
					winning_tiles.push_back(tile);

					tile.first = almost_combo_tiles[1].first + 1;
					tile.second = almost_combo_tiles[1].second;
					winning_tiles.push_back(tile);
				}
			}
			//if tile missing in between
			else if (almost_combo_tiles[0].first == almost_combo_tiles[1].first - 2)
			{
				tile.first = almost_combo_tiles[0].first + 1;
				tile.second = almost_combo_tiles[0].second;
				winning_tiles.push_back(tile);
			}
		}
	}

	return winning_tiles;
}

void Player::erase_from_hand(pair<int, string> tile_1, pair<int, string> tile_2)
{
	vector<pair<int, string>>::iterator it = hand.begin();
	while (it != hand.end())
	{
		if ((*it) == tile_1)
		{
			it = hand.erase(it);
			break;
		}
		else
			it++;
	}

	it = hand.begin();
	while (it != hand.end())
	{
		if ((*it) == tile_2)
		{
			it = hand.erase(it);
			break;
		}
		else
			it++;
	}
}

void Player::print_combos()
{
	int counter = 1;
	vector<vector<pair<int, string>>>::iterator it = combos.begin();
	while (it != combos.end())
	{
		cout << "Combo " << counter << ": ";
		if ((*it)[0].first == 0)
			cout << (*it)[0].second << ", "
				<< (*it)[1].second << ", "
				<< (*it)[2].second << endl;
		else
			cout << (*it)[0].first << " " << (*it)[0].second << ", " 
			<< (*it)[1].first << " " << (*it)[1].second << ", " 
			<< (*it)[2].first << " " << (*it)[2].second << endl;

		counter++;
		it++;
	}
}

void Player::fix_non_combo_tiles()
{
	//find all tiles that are almost a combo and remove them
	if (non_combo_tiles.empty() || non_combo_tiles.size() == 1)
		return;

	almost_combo_tiles.clear();
	vector<pair<int, string>>::iterator it = non_combo_tiles.begin();
	while (it != non_combo_tiles.end() && it != non_combo_tiles.end() - 1)
	{
		vector<pair<int, string>>::iterator it2 = it + 1;
		if ((*it).second == (*it2).second)
		{
			if ((*it).first == (*it2).first  ||
				(*it).first == (*it2).first - 1 ||
				(*it).first == (*it2).first - 2)
			{
				almost_combo_tiles.push_back(*it);
				almost_combo_tiles.push_back(*it2);
				it = non_combo_tiles.erase(it, it2 + 1);
			}
			else
				it++;
		}
		else
			it++;
	}
}

//test
void Player::set_hand(vector<pair<int, string>> input)
{
	hand = input;
}

void Player::print_hand()
{
	for (int i = 0; i < hand.size(); i++)
	{
		std::cout << hand[i].first << " " << hand[i].second << endl;
	}
}

int Player::get_hand_size()
{
	return hand.size() + (combos.size() * 3);
}