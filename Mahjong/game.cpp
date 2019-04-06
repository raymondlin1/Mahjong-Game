#include "stdafx.h"
#include <iostream>
#include "game.h"
using namespace std;

int FIRST_PLAYER_HAND_SIZE = 14;

void increment_turn(int &turn);
int increment_turn_2(int turn);
string increment_wind(string wind);
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

	player = new User();
	cpu_1 = new Cpu("cpu_1");
	cpu_2 = new Cpu("cpu_2");
	cpu_3 = new Cpu("cpu_3");
	deck->deal(player->get_hand(), cpu_1->get_hand(), cpu_2->get_hand(), cpu_3->get_hand(), -1);
	player->sort_hand();
	cpu_1->sort_hand();
	cpu_2->sort_hand();
	cpu_3->sort_hand();
	game_over = false;
	wind = "East";
	winner = -1;
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
	print_balances();

	if (player->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		first_player = 0;
	else if (cpu_1->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		first_player = 1;
	else if (cpu_2->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		first_player = 2;
	else if (cpu_3->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		first_player = 3;

	bool new_game = true;
	while (new_game)
	{
		cout << "Wind is blowing towards the " << wind << endl;
		//order: 0-player, 1-cpu1, 2-cpu2, 3-cpu3
		int turn;
		pair<int, string> temp;

		//get first player
		if (player->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		{
			turn = 0;
			print_player_hand();
			if (player->has_winning_hand())
			{
				winner = 0;
				game_over = declare_victory("player");
			}

			temp = player->throw_tile();
		}
		else if (cpu_1->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		{
			turn = 1;
			if (cpu_1->has_winning_hand())
			{
				winner = 1;
				game_over = declare_victory(cpu_1->get_name());
			}

			temp = cpu_1->throw_tile();
		}
		else if (cpu_2->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		{
			turn = 2;
			if (cpu_2->has_winning_hand())
			{
				winner = 2;
				game_over = declare_victory(cpu_2->get_name());
			}

			temp = cpu_2->throw_tile();
		}
		else if (cpu_3->get_hand().size() == FIRST_PLAYER_HAND_SIZE)
		{
			turn = 3;
			if (cpu_3->has_winning_hand())
			{
				winner = 3;
				game_over = declare_victory(cpu_3->get_name());
			}

			temp = cpu_3->throw_tile();
		}

		//if anyone has a combo
		check_combos(temp, turn);

		increment_turn(turn);
		//print_field();

		//game loop
		while (!game_over)
		{
			if (deck->is_empty())
			{
				game_over = true;
				cout << "Game over! The deck is empty! It's a tie!" << endl;
				break;
			}

			//hand check
			if (cpu_1->get_hand_size() != 13 ||
				cpu_2->get_hand_size() != 13 ||
				cpu_3->get_hand_size() != 13 ||
				player->get_hand_size() != 13)
			{
				cout << "Error: one of the player's hand sizes is incorrect" << endl;
				exit(1);
			}

			//draw
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
				{
					winner = 0;
					game_over = declare_victory("player");
					continue;
				}
				else
					temp = player->throw_tile();

				break;
			case 1:
				deck->draw_tile(cpu_1->get_hand());
				cpu_1->sort_hand();
				if (cpu_1->has_winning_hand())
				{
					winner = 1;
					game_over = declare_victory(cpu_1->get_name());
					continue;
				}
				else
					temp = cpu_1->throw_tile();

				break;
			case 2:
				deck->draw_tile(cpu_2->get_hand());
				cpu_2->sort_hand();
				if (cpu_2->has_winning_hand())
				{
					winner = 2;
					game_over = declare_victory(cpu_2->get_name());
					continue;
				}
				else
					temp = cpu_2->throw_tile();

				break;
			case 3:
				deck->draw_tile(cpu_3->get_hand());
				cpu_3->sort_hand();
				if (cpu_3->has_winning_hand())
				{
					winner = 3;
					game_over = declare_victory(cpu_3->get_name());
					continue;
				}
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
			if(!game_over)
				increment_turn(turn);
		}

		calculate_pay(turn);
		print_balances();

		cout << "Would you like to play again?" << endl;
		bool valid = false;
		while (!valid)
		{
			string input;
			getline(cin, input);
			if (input == "Y" || input == "y" || input == "yes" || input == "Yes")
			{
				//determine the next dealer
				int new_dealer;
				if (winner == deck->get_dealer())
					new_dealer = winner;
				else
					new_dealer = increment_turn_2(deck->get_dealer());

				if (new_dealer == first_player && winner != first_player)
					wind = increment_wind(wind);

				valid = true;
				game_over = false;
				delete deck;
				cpu_1->clear_structures();
				cpu_2->clear_structures();
				cpu_3->clear_structures();
				player->clear_structures();
				deck = new Deck();
				deck->shuffle();
				deck->deal(player->get_hand(), cpu_1->get_hand(), cpu_2->get_hand(), cpu_3->get_hand(), new_dealer);
				player->sort_hand();
				cpu_1->sort_hand();
				cpu_2->sort_hand();
				cpu_3->sort_hand();
				field_tiles.clear();
			}
			else if (input == "N" || input == "n" || input == "no" || input == "No")
			{
				valid = true;
				new_game = false;
			}
			else
			{
				cout << "Please enter a valid input." << endl;
			}
		}
	}
}

void increment_turn(int &turn)
{
	if (turn == 3)
		turn = 0;
	else
		turn++;
}

int increment_turn_2(int turn)
{
	if (turn == 3)
		return 0;
	else
		return turn + 1;
}

string increment_wind(string wind)
{
	if (wind == "East")
		return "South";
	else if (wind == "South")
		return "West";
	else if (wind == "West")
		return "North";
	else if (wind == "North")
		return "East";
}

bool Game::declare_victory(string name)
{
	if (name == "player")
	{
		cout << "You have won!!!! Congratulations!" << endl;
		return true;
	}
	else if (name == "cpu_1")
	{
		cout << name << " has declared victory! You lose!" << endl;
		cpu_1->print_hand();
		cpu_1->print_combos();
		return true;
	}
	else if (name == "cpu_2")
	{
		cout << name << " has declared victory! You lose!" << endl;
		cpu_2->print_hand();
		cpu_2->print_combos();
		return true;
	}
	else if (name == "cpu_3")
	{
		cout << name << " has declared victory! You lose!" << endl;
		cpu_3->print_hand();
		cpu_3->print_combos();
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
	pair<int, string> thrown;
	//if anyone has a combo
	bool won = false;
	if ((player->has_combo(temp, turn) && turn != 0) || (won = is_in_vector(player->almost_won(), temp)))
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
				if (player->has_winning_hand() || won)
				{
					winner = 0;
					game_over = declare_victory("player");
				}
				else
				{
					turn = 0;
					thrown = player->throw_tile();
					check_combos(thrown, turn);
				}
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
	else if ((cpu_1->has_combo(temp, turn) && turn != 1) || (won = is_in_vector(cpu_1->almost_won(), temp)))
	{
		cout << "CPU 1 took the ";
		if (temp.first == 0)
			cout << temp.second << endl;
		else
			cout << temp.first << " of " << temp.second << endl;

		cpu_1->print_combos();
		cpu_1->sort_hand();
		if (cpu_1->has_winning_hand())
		{
			winner = 1;
			game_over = declare_victory(cpu_1->get_name());
		}
		else if (won)
		{
			winner = 1;
			cpu_1->add_tile(temp);
			cpu_1->sort_hand();
			game_over = declare_victory(cpu_1->get_name());
		}
		else
		{
			turn = 1;
			thrown = cpu_1->throw_tile();
			check_combos(thrown, turn);
		}
	}
	else if ((cpu_2->has_combo(temp, turn) && turn != 2) || (won = is_in_vector(cpu_2->almost_won(), temp)))
	{
		cout << "CPU 2 took the ";
		if (temp.first == 0)
			cout << temp.second << endl;
		else
			cout << temp.first << " of " << temp.second << endl;

		cpu_2->print_combos();
		cpu_2->sort_hand();
		if (cpu_2->has_winning_hand())
		{
			winner = 2;
			game_over = declare_victory(cpu_2->get_name());
		}
		else if (won)
		{
			winner = 2;
			cpu_2->add_tile(temp);
			cpu_2->sort_hand();
			game_over = declare_victory(cpu_2->get_name());
		}
		else
		{
			turn = 2;
			thrown = cpu_2->throw_tile();
			check_combos(thrown, turn);
		}
	}
	else if ((cpu_3->has_combo(temp, turn) && turn != 3) || (won = is_in_vector(cpu_3->almost_won(), temp)))
	{
		cout << "CPU 3 took the ";
		if (temp.first == 0)
			cout << temp.second << endl;
		else
			cout << temp.first << " of " << temp.second << endl;

		cpu_3->print_combos();
		cpu_3->sort_hand();
		if (cpu_3->has_winning_hand())
		{
			winner = 3;
			game_over = declare_victory(cpu_3->get_name());
		}
		else if (won)
		{
			winner = 3;
			cpu_3->add_tile(temp);
			cpu_3->sort_hand();
			game_over = declare_victory(cpu_3->get_name());
		}
		else
		{
			turn = 3;
			thrown = cpu_3->throw_tile();
			check_combos(thrown, turn);
		}
	}
	else
	{
		field_tiles.push_back(temp);
	}
}

void Game::calculate_pay(int turn)
{
	double amount;
	if (winner == turn)
	{
		//collect money from everyone
		switch (turn)
		{
		case 0:
			amount = player->calculate_payout(wind);
			player->change_balance(amount * 3);
			cpu_1->change_balance(-amount);
			cpu_2->change_balance(-amount);
			cpu_3->change_balance(-amount);
			cout << "All players paid $" << amount << " to you." << endl;
			break;
		case 1:
			amount = cpu_1->calculate_payout(wind);
			player->change_balance(-amount);
			cpu_1->change_balance(amount * 3);
			cpu_2->change_balance(-amount);
			cpu_3->change_balance(-amount);
			cout << "All players paid $" << amount << " to Cpu 1." << endl;
			break;
		case 2:
			amount = cpu_2->calculate_payout(wind);
			player->change_balance(-amount);
			cpu_1->change_balance(-amount);
			cpu_2->change_balance(amount * 3);
			cpu_3->change_balance(-amount);
			cout << "All players paid $" << amount << " to Cpu 2." << endl;
			break;
		case 3:
			amount = cpu_3->calculate_payout(wind);
			player->change_balance(-amount);
			cpu_1->change_balance(-amount);
			cpu_2->change_balance(-amount);
			cpu_3->change_balance(amount * 3);
			cout << "All players paid $" << amount << " to Cpu 3." << endl;
			break;
		default:
			cout << "Error: wrong turn." << endl;
			exit(1);
		}
	}
	else
	{
		switch (winner)
		{
		case 0:
			amount = player->calculate_payout(wind);
			break;
		case 1:
			amount = cpu_1->calculate_payout(wind);
			break;
		case 2:
			amount = cpu_2->calculate_payout(wind);
			break;
		case 3:
			amount = cpu_3->calculate_payout(wind);
			break;
		default:
			cout << "Error: winner has not been set." << endl;
			exit(1);
		}

		switch (turn)
		{
		case 0:
			player->change_balance(-amount);
			cout << "Player paid $" << amount;
			break;
		case 1:
			cpu_1->change_balance(-amount);
			cout << "Cpu 1 paid $" << amount;
			break;
		case 2:
			cpu_2->change_balance(-amount);
			cout << "Cpu 2 paid $" << amount;
			break;
		case 3:
			cpu_3->change_balance(-amount);
			cout << "Cpu 3 paid $" << amount;
			break;
		default:
			cout << "Error: wrong turn." << endl;
			exit(1);
		}

		switch (winner)
		{
		case 0:
			player->change_balance(amount);
			cout << " to player." << endl;
			break;
		case 1:
			cpu_1->change_balance(amount);
			cout << " to Cpu 1." << endl;
			break;
		case 2:
			cpu_2->change_balance(amount);
			cout << " to Cpu 2." << endl;
			break;
		case 3:
			cpu_3->change_balance(amount);
			cout << " to Cpu 3." << endl;
			break;
		default:
			cout << "Error: winner has not been set." << endl;
			exit(1);
		}
	}
}

void Game::print_balances()
{
	cout << "Player balance: $" << player->get_balance() << endl;
	cout << "Cpu 1 balance: $" << cpu_1->get_balance() << endl;
	cout << "Cpu 2 balance: $" << cpu_2->get_balance() << endl;
	cout << "Cpu 3 balance: $" << cpu_3->get_balance() << endl;
}