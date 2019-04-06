#include "stdafx.h"
#include "deck.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int DECK_SIZE = 144;
int HAND_SIZE = 13;

Deck::Deck()
{
	//4 of each tile
	for (int k = 0; k < 4; k++)
	{
		//suite tiles
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				pair<int, string> temp;
				switch (j)
				{
				case 0:
					temp.first = i;
					temp.second = "Circles";
					break;
				case 1:
					temp.first = i;
					temp.second = "Bamboos";
					break;
				case 2:
					temp.first = i;
					temp.second = "Characters";
					break;
				default:
					cout << "Error adding tiles to board!" << endl;
					break;
				}
				tiles.push_back(temp);
			}
		}

		//bonus tiles
		pair<int, string> temp_2;
		temp_2.first = 0;
		temp_2.second = "East";
		tiles.push_back(temp_2);

		temp_2.second = "West";
		tiles.push_back(temp_2);

		temp_2.second = "North";
		tiles.push_back(temp_2);

		temp_2.second = "South";
		tiles.push_back(temp_2);

		temp_2.second = "Red Middle";
		tiles.push_back(temp_2);

		temp_2.second = "White Board";
		tiles.push_back(temp_2);

		temp_2.second = "Green Good Luck";
		tiles.push_back(temp_2);
	}

	//flower tiles
	pair<int, string> temp_3;
	temp_3.first = 0;
	temp_3.second = "Flower 1";
	tiles.push_back(temp_3);
	tiles.push_back(temp_3);

	temp_3.second = "Flower 2";
	tiles.push_back(temp_3);
	tiles.push_back(temp_3);

	temp_3.second = "Flower 3";
	tiles.push_back(temp_3);
	tiles.push_back(temp_3);

	temp_3.second = "Flower 4";
	tiles.push_back(temp_3);
	tiles.push_back(temp_3);
}

void Deck::print_deck()
{
	vector<pair<int,string>>::iterator it = tiles.begin();
	while (it != tiles.end())
	{
		cout << (*it).second << endl;
		it++;
	}
}

bool Deck::check_size()
{
	if (tiles.size() == DECK_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Deck::shuffle()
{
	srand(time(0));
	for (int i = 0; i < 20; i++)
	{
		vector<pair<int, string>> temp1;
		vector<pair<int, string>> temp2;

		vector<pair<int, string>>::iterator it = tiles.begin();
		//split tiles into two vectors
		while (it != tiles.end())
		{
			int random = rand() % 2;
			if (random)
			{
				temp1.push_back(*it);
				it = tiles.erase(it);
			}
			else
			{
				temp2.push_back(*it);
				it = tiles.erase(it);
			}
		}

		//check if tiles is empty
		if (tiles.size() != 0)
		{
			cout << "Error: shuffling failed" << endl;
			return;
		}

		//recombine them
		vector<pair<int, string>>::iterator it1 = temp1.begin();
		vector<pair<int, string>>::iterator it2 = temp2.begin();
		for (int i = 0; i < DECK_SIZE; i++)
		{
			if (i % 2)
			{
				if(it1 != temp1.end())
				{
					tiles.push_back(*it1);
					it1 = temp1.erase(it1);
				}
				else if (it2 != temp2.end())
				{
					tiles.push_back(*it2);
					it2 = temp2.erase(it2);
				}
			}
			else
			{
				if (it2 != temp2.end())
				{
					tiles.push_back(*it2);
					it2 = temp2.erase(it2);
				}
				else if (it1 != temp1.end())
				{
					tiles.push_back(*it1);
					it1 = temp1.erase(it1);
				}
			}
				
		}

		if (!check_size())
		{
			cout << "Error: in shuffle, deck has INCORRECT size" << endl;
			return;
		}
	}

	cout << "Deck successfully shuffled!" << endl;
}

void Deck::deal(vector<pair<int, string>> &player, vector<pair<int, string>> &cpu1, vector<pair<int, string>> &cpu2, 
	vector<pair<int, string>> &cpu3, int turn)
{
	for(int j = 0; j < 3; j++)
	{
		vector<pair<int, string>>::iterator it = tiles.begin();
		for (int i = 0; i < 4; i++)
		{
			player.push_back(*it);
			it = tiles.erase(it);
		}

		it = tiles.begin();
		for (int i = 0; i < 4; i++)
		{
			cpu1.push_back(*it);
			it = tiles.erase(it);
		}

		it = tiles.begin();
		for (int i = 0; i < 4; i++)
		{
			cpu2.push_back(*it);
			it = tiles.erase(it);
		}

		it = tiles.begin();
		for (int i = 0; i < 4; i++)
		{
			cpu3.push_back(*it);
			it = tiles.erase(it);
		}
	}

	vector<pair<int, string>>::iterator it = tiles.begin();
	player.push_back(*it);
	it = tiles.erase(it);
	cpu1.push_back(*it);
	it = tiles.erase(it);
	cpu2.push_back(*it);
	it = tiles.erase(it);
	cpu3.push_back(*it);
	it = tiles.erase(it);

	//check hand sizes
	if (player.size() != HAND_SIZE || cpu1.size() != HAND_SIZE || cpu2.size() != HAND_SIZE || cpu3.size() != HAND_SIZE)
	{
		cout << "Error: in deal, hand sizes are incorrect!" << endl;
		return;
	}

	if (turn == -1)
	{
		srand(time(0));
		int random = rand() % 4;
		switch (random)
		{
		case 0:
		{
			cout << "Player has been selected as the dealer!" << endl;
			vector<pair<int, string>>::iterator it = tiles.begin();
			player.push_back(*it);
			tiles.erase(it);
			dealer = 0;
			break;
		}
		case 1:
		{
			cout << "CPU 1 has been selected as the dealer!" << endl;
			vector<pair<int, string>>::iterator it = tiles.begin();
			cpu1.push_back(*it);
			tiles.erase(it);
			dealer = 1;
			break;
		}
		case 2:
		{
			cout << "CPU 2 has been selected as the dealer!" << endl;
			vector<pair<int, string>>::iterator it = tiles.begin();
			cpu2.push_back(*it);
			tiles.erase(it);
			dealer = 2;
			break;
		}
		case 3:
		{
			cout << "CPU 3 has been selected as the dealer!" << endl;
			vector<pair<int, string>>::iterator it = tiles.begin();
			cpu3.push_back(*it);
			tiles.erase(it);
			dealer = 3;
			break;
		}
		default:
			cout << "something wrong with mod 4." << endl;
		}
	}
	else if (turn == 0)
	{
		cout << "Player has been selected as the dealer!" << endl;
		vector<pair<int, string>>::iterator it = tiles.begin();
		player.push_back(*it);
		tiles.erase(it);
		dealer = 0;
	}
	else if (turn == 1)
	{
		cout << "CPU 1 has been selected as the dealer!" << endl;
		vector<pair<int, string>>::iterator it = tiles.begin();
		cpu1.push_back(*it);
		tiles.erase(it);
		dealer = 1;
	}
	else if (turn == 2)
	{
		cout << "CPU 2 has been selected as the dealer!" << endl;
		vector<pair<int, string>>::iterator it = tiles.begin();
		cpu2.push_back(*it);
		tiles.erase(it);
		dealer = 2;
	}
	else if (turn == 3)
	{
		cout << "CPU 3 has been selected as the dealer!" << endl;
		vector<pair<int, string>>::iterator it = tiles.begin();
		cpu3.push_back(*it);
		tiles.erase(it);
		dealer = 3;
	}
	else
	{
		cout << "invalid turn" << endl;
		exit(1);
	}
}

pair<int, string> Deck::draw_tile(vector<pair<int, string>> &hand)
{
	vector<pair<int, string>>::iterator it = tiles.begin();
	hand.push_back(*it);
	pair<int, string> temp = *it;
	tiles.erase(it);
	return temp;
}

bool Deck::is_empty()
{
	if (tiles.size() == 0)
		return true;
	return false;
}

int& Deck::get_dealer()
{
	return dealer;
}

bool Deck::set_dealer(int input)
{
	if (input < 0 || input > 3)
		return false;

	dealer = input;
	return true;
}