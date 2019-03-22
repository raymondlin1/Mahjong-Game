#include "stdafx.h"
#include <iostream>
#include "game.h"
using namespace std;

int FIRST_PLAYER_HAND_SIZE = 13;

void increment_turn(int &turn);

Game::Game()
{
	deck = new Deck();
	if (!deck->check_size())
	{
		cout << "Deck has INCORRECT size!" << endl;
		exit(1);
	}
	else
	{
		cout << "Deck successfully created!" << endl;
	}
	deck->shuffle();
	//deck->print_deck();

	player = new User();
	cpu_1 = new Cpu("cpu_1");
	cpu_2 = new Cpu("cpu_2");
	cpu_3 = new Cpu("cpu_3");
	deck->deal(player->get_hand(), cpu_1->get_hand(), cpu_2->get_hand(), cpu_3->get_hand());
	player->sort_hand();
	cpu_1->sort_hand();
	cpu_2->sort_hand();
	cpu_3->sort_hand();
	game_over = false;
}

void Game::print_hands()
{
	cout << "Player's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = player->get_hand().begin(); it != player->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cout << endl;

	cout << "cpu1's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = cpu_1->get_hand().begin(); it != cpu_1->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cout << endl;

	cout << "cpu2's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = cpu_2->get_hand().begin(); it != cpu_2->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cout << endl;

	cout << "cpu3's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = cpu_3->get_hand().begin(); it != cpu_3->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cout << endl;
}

void Game::print_player_hand()
{
	cout << "Your hand: " << endl;
	for (vector<pair<int, string>>::iterator it = player->get_hand().begin(); it != player->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cout << endl;
}

void Game::print_field()
{
	cout << "Here are the tiles on the field" << endl;
	for (int i = 0; i < field_tiles.size(); i++)
	{
		cout << field_tiles[i].first << " " << field_tiles[i].second << endl;
	}

	cout << endl;
}

void Game::play_game()
{
	//order: 0-player, 1-cpu1, 2-cpu2, 3-cpu3
	int turn;

	//get first player
	if (player->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 0;
		print_player_hand();
		pair<int, string> temp = player->throw_tile();
		field_tiles.push_back(temp);
	}
	else if (cpu_1->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 1;
		pair<int, string> temp = cpu_1->throw_tile();
		field_tiles.push_back(temp);
	}
	else if (cpu_2->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 2;
		pair<int, string> temp = cpu_2->throw_tile();
		field_tiles.push_back(temp);
	}
	else if (cpu_3->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 3;
		pair<int, string> temp = cpu_3->throw_tile();
		field_tiles.push_back(temp);
	}

	increment_turn(turn);
	//print_field();
	pair<int, string> temp;
	while (!game_over)
	{
		switch (turn)
		{
		case 0:
			temp = deck->draw_tile(player->get_hand());
			print_field();
			cout << "You drew a " << temp.first << " " << temp.second << endl;
			player->sort_hand();
			print_player_hand();
			field_tiles.push_back(player->throw_tile());
			break;
		case 1:
			deck->draw_tile(cpu_1->get_hand());
			temp = cpu_1->throw_tile();
			break;
		case 2:
			deck->draw_tile(cpu_2->get_hand());
			temp = cpu_2->throw_tile();
			break;
		case 3:
			deck->draw_tile(cpu_3->get_hand());
			temp = cpu_3->throw_tile();
			break;
		default:
			cout << "Error: Turn incrementing failed!" << endl;
			game_over = true;
		}

		if (player->has_combo(temp, turn) && turn != 0)
		{
			print_field();
			print_player_hand();
			cout << "Would you like to take the tile?" << endl;
			
			bool valid = false;
			while (!valid)
			{
				string input;
				getline(cin, input);

				if (input == "yes" || input == "Yes" || input == "y" || input == "Y")
				{
					turn = 0;
					valid = true;
					player->add_tile(temp);
					player->throw_tile();
				}
				else if (input == "no" || input == "No" || input == "n" || input == "N")
				{
					valid = true;
				}
				else
				{
					cout << "Please enter a valid input" << endl;
				}
			}
		}
		else
		{
			field_tiles.push_back(temp);
		}

		cout << endl;
		increment_turn(turn);
	}
}

void increment_turn(int &turn)
{
	if (turn == 3)
		turn = 0;
	else
		turn++;
}