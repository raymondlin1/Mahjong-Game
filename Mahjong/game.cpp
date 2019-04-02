#include "stdafx.h"
#include <iostream>
#include "game.h"
using namespace std;

int FIRST_PLAYER_HAND_SIZE = 14;

void increment_turn(int &turn);
bool is_in_vector(vector<pair<int, string>> input, pair<int, string> tile);

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

	player->print_combos();
	cout << endl;

	cout << "cpu1's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = cpu_1->get_hand().begin(); it != cpu_1->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cpu_1->print_combos();
	cout << endl;

	cout << "cpu2's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = cpu_2->get_hand().begin(); it != cpu_2->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cpu_2->print_combos();
	cout << endl;

	cout << "cpu3's hand: " << endl;
	for (vector<pair<int, string>>::iterator it = cpu_3->get_hand().begin(); it != cpu_3->get_hand().end(); it++)
	{
		if ((*it).first != 0)
			cout << (*it).first << " ";
		cout << (*it).second << endl;
	}

	cpu_3->print_combos();
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

	player->print_combos();
	cout << endl;
}

void Game::print_field()
{
	cout << "Here are the tiles on the field" << endl;
	for (int i = 0; i < field_tiles.size(); i++)
	{
		if (field_tiles[i].first == 0)
			cout << field_tiles[i].second << endl;
		else
			cout << field_tiles[i].first << " " << field_tiles[i].second << endl;
	}

	cout << endl;
}

void Game::play_game()
{
	//order: 0-player, 1-cpu1, 2-cpu2, 3-cpu3
	int turn;
	pair<int, string> temp;

	//get first player
	if (player->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 0;
		print_player_hand();
		if (player->has_winning_hand())
			declare_victory("player");

		temp = player->throw_tile();
	}
	else if (cpu_1->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 1;
		if (cpu_1->has_winning_hand())
			declare_victory(cpu_1->get_name());

		temp = cpu_1->throw_tile();
	}
	else if (cpu_2->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 2;
		if (cpu_2->has_winning_hand())
			declare_victory(cpu_2->get_name());

		temp = cpu_2->throw_tile();
	}
	else if (cpu_3->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
	{
		turn = 3;
		if (cpu_3->has_winning_hand())
			declare_victory(cpu_3->get_name());

		temp = cpu_3->throw_tile();
	}

	//if anyone has a combo
	check_combos(temp, turn);

	increment_turn(turn);
	//print_field();
	
	while (!game_over)
	{
		if (deck->is_empty())
		{
			game_over = true;
			cout << "Game over! The deck is empty! It's a tie!" << endl;
			break;
		}

		switch (turn)
		{
		case 0:
			temp = deck->draw_tile(player->get_hand());
			print_field();
			
			cout << "You drew a ";
			if (temp.first == 0)
				cout << temp.second << endl;
			else
				cout << temp.first << " of " << temp.second << endl;

			player->sort_hand();
			print_player_hand();
			if (player->has_winning_hand())
				game_over = declare_victory("player");
			else
				temp = player->throw_tile();

			break;
		case 1:
			deck->draw_tile(cpu_1->get_hand());
			cpu_1->sort_hand();
			if (cpu_1->has_winning_hand())
				game_over = declare_victory(cpu_1->get_name());
			else
				temp = cpu_1->throw_tile();

			break;
		case 2:
			deck->draw_tile(cpu_2->get_hand());
			cpu_2->sort_hand();
			if (cpu_2->has_winning_hand())
				game_over = declare_victory(cpu_2->get_name());
			else
				temp = cpu_2->throw_tile();

			break;
		case 3:
			deck->draw_tile(cpu_3->get_hand());
			cpu_3->sort_hand();
			if (cpu_3->has_winning_hand())
				game_over = declare_victory(cpu_3->get_name());
			else
				temp = cpu_3->throw_tile();

			break;
		default:
			cout << "Error: Turn incrementing failed!" << endl;
			game_over = true;
		}
		
		//if anyone has a combo
		check_combos(temp, turn);

		cout << endl;
		increment_turn(turn);
	}

	print_hands();
}

void increment_turn(int &turn)
{
	if (turn == 3)
		turn = 0;
	else
		turn++;
}

bool Game::declare_victory(string name)
{
	if (name == "player")
	{
		cout << "You have a winning combo. Would you like to declare victory?" << endl;

		bool valid_input = false;
		string input;
		while (!valid_input)
		{
			getline(cin, input);
			if (input == "yes" || input == "Yes" || input == "Y" || input == "y")
			{
				cout << "You have won!!!! Congratulations!" << endl;
				return true;
			}
			else if (input == "no" || input == "No" || input == "N" || input == "n")
			{
				valid_input = true;
			}
			else
			{
				cout << "Please enter a valid input" << endl;
			}
		}

		return false;
	}
	
	if (name == "cpu_1")
	{
		cout << name << " has declared victory! You lose!" << endl;
		cpu_1->print_hand();
		return true;
	}
	else if (name == "cpu_2")
	{
		cout << name << " has declared victory! You lose!" << endl;
		cpu_2->print_hand();
		return true;
	}
	else if (name == "cpu_3")
	{
		cout << name << " has declared victory! You lose!" << endl;
		cpu_3->print_hand();
		return true;
	}
	else
	{
		cout << "wrong name was inputted into 'declare_victory'. ending game now" << endl;
		return true;
	}
}

bool is_in_vector(vector<pair<int, string>> input, pair<int, string> tile)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == tile)
			return true;
	}

	return false;
}

void Game::check_combos(pair<int, string> &temp, int &turn)
{
	//if anyone has a combo
	if ((player->has_combo(temp, turn) && turn != 0) || is_in_vector(player->almost_won(), temp))
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
				valid = true;
				player->has_combo(temp, turn, true);
				turn = 0;
				if (player->has_winning_hand())
					game_over = declare_victory("player");
				else
					field_tiles.push_back(player->throw_tile());
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
	else if ((cpu_1->has_combo(temp, turn) && turn != 1) || is_in_vector(cpu_1->almost_won(), temp))
	{
		turn = 1;
		cout << "CPU 1 took the ";
		if (temp.first == 0)
			cout << temp.second << endl;
		else
			cout << temp.first << " of " << temp.second << endl;

		cpu_1->print_combos();
		cpu_1->sort_hand();
		if (cpu_1->has_winning_hand())
			game_over = declare_victory(cpu_1->get_name());
		else
			field_tiles.push_back(cpu_1->throw_tile());
	}
	else if ((cpu_2->has_combo(temp, turn) && turn != 2) || is_in_vector(cpu_2->almost_won(), temp))
	{
		turn = 2;
		cout << "CPU 2 took the ";
		if (temp.first == 0)
			cout << temp.second << endl;
		else
			cout << temp.first << " of " << temp.second << endl;

		cpu_2->print_combos();
		cpu_2->sort_hand();
		if (cpu_2->has_winning_hand())
			game_over = declare_victory(cpu_2->get_name());
		else
			field_tiles.push_back(cpu_2->throw_tile());
	}
	else if ((cpu_3->has_combo(temp, turn) && turn != 3) || is_in_vector(cpu_3->almost_won(), temp))
	{
		turn = 3;
		cout << "CPU 3 took the ";
		if (temp.first == 0)
			cout << temp.second << endl;
		else
			cout << temp.first << " of " << temp.second << endl;

		cpu_3->print_combos();
		cpu_3->sort_hand();
		if (cpu_3->has_winning_hand())
			game_over = declare_victory(cpu_3->get_name());
		else
			field_tiles.push_back(cpu_3->throw_tile());
	}
	else
	{
		field_tiles.push_back(temp);
	}
}