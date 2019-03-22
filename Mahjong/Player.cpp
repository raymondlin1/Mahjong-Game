#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include <iostream>

int CPU_BEFORE_PLAYER = 3;

void bubble_sort_hand(vector<pair<int, string>> &arr, bool first, int start, int end);

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
	while (index != hand.size() - 1)
	{
		if (hand[index].second != hand[index + 1].second)
		{
			bubble_sort_hand(hand, true, start, index + 1);
			start = index + 1;
		}
		index++;
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

bool Player::has_combo(pair<int, string> tile, int turn)
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

void Player::add_tile(pair<int, string> tile)
{
	hand.push_back(tile);
}

bool Player::has_winning_hand()
{
	vector<pair<int,string>> copy = hand;
	vector<vector<pair<int, string>>> combos;

	//first check for all possible combos
	for (int i = 0; i < copy.size() - 2; i++)
	{
		if (copy[i] == copy[i + 1] && copy[i] == copy[i + 2])
		{
			vector<pair<int, string>> temp;
			temp.push_back(copy[i]);
			temp.push_back(copy[i + 1]);
			temp.push_back(copy[i + 2]);
			combos.push_back(temp);
		}
		else if (copy[i].second == copy[i + 1].second && copy[i].first == copy[i + 1].first - 1
			&& copy[i + 1].second == copy[i + 2].second && copy[i + 1].first == copy[i + 2].first - 1)
		{
			vector<pair<int, string>> temp;
			temp.push_back(copy[i]);
			temp.push_back(copy[i + 1]);
			temp.push_back(copy[i + 2]);
			combos.push_back(temp);
		}
	}

	//print out combos vector for testing
	for (int i = 0; i < combos.size(); i++)
	{
		cout << "combo " << i << endl;
		for (int j = 0; j < combos[i].size(); j++)
		{
			std::cout << combos[i][j].first << " " << combos[i][j].second << std::endl;
		}
	}
	return true;
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