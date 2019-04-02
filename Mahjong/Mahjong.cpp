// Mahjong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "deck.h"
#include "game.h"
using namespace std;

int main()
{
	Game* game = new Game();
	game->play_game();

	/*User test;
	vector<pair<int, string>> input;
	pair<int, string> tile;

	//1
	tile.first = 1;
	tile.second = "Bamboos";
	input.push_back(tile);

	//2
	tile.first = 2;
	tile.second = "Bamboos";
	input.push_back(tile);

	//3
	tile.first = 3;
	tile.second = "Bamboos";
	input.push_back(tile);

	//4
	tile.first = 4;
	tile.second = "Circles";
	input.push_back(tile);

	//5
	tile.first = 5;
	tile.second = "Circles";
	input.push_back(tile);

	//6
	tile.first = 6;
	tile.second = "Circles";
	input.push_back(tile);

	//7
	tile.first = 7;
	tile.second = "Bamboos";
	input.push_back(tile);

	//8
	tile.first = 8;
	tile.second = "Bamboos";
	input.push_back(tile);

	//9
	tile.first = 9;
	tile.second = "Bamboos";
	input.push_back(tile);

	//10
	tile.first = 2;
	tile.second = "Characters";
	input.push_back(tile);

	//11
	tile.first = 2;
	tile.second = "Characters";
	input.push_back(tile);

	//12
	tile.first = 6;
	tile.second = "Circles";
	input.push_back(tile);

	//13
	tile.first = 6;
	tile.second = "Circles";
	input.push_back(tile);

	//14
	tile.first = 6;
	tile.second = "Circles";
	input.push_back(tile);

	test.set_hand(input);
	test.sort_hand();
	test.print_hand();
	cout << endl;
	
	if (test.has_winning_hand())
		cout << "true" << endl;
	else
		cout << "false" << endl;
	*/
    return 0;
}

