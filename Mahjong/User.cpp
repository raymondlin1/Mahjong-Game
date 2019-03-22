#include "stdafx.h"
#include "User.h"
#include <iostream>

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

		if (thrown == "West" || thrown == "East" || thrown == "North" || thrown == "South" 
			|| thrown == "Flower 1" || thrown == "Flower 2"  || thrown == "Flower 3" || thrown == "Flower 4"
			|| thrown == "Red Middle" || thrown == "Green Good Luck" || thrown == "White Board")
		{
			tile.first = 0;
			tile.second = thrown;
			break;
		}

		if (isdigit(thrown[0]))
		{
			tile.first = thrown[0] - 48; 
			string sub_string = thrown.substr(2, thrown.length());
			if (sub_string == "Bamboos" || sub_string == "Characters" || sub_string == "Circles")
			{
				tile.second = sub_string;
				valid_input = true;
				break;
			}
		}
		else
		{
			cout << "Please enter a valid tile" << endl;
			continue;
		}
	}
	
	vector<pair<int, string>>::iterator it = hand.begin();
	while (it != hand.end())
	{
		if((*it).first == tile.first && (*it).second == tile.second)
			break;
		it++;
	}

	cout << "You threw out a " << tile.first << " of " << tile.second << endl;
	hand.erase(it);

	return tile;
}