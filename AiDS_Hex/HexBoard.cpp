#include "HexBoard.h"
#include <iostream>
#include <string>

using std::cin;
using std::string;

HexBoard::HexBoard()
{
	redPawnsNumber = 0;
	bluePawnsNumber = 0;
	string input;
	cin >> input; // "---"
	int i = 0;
	do
	{
		board.push_back(new vector<Hex*>());
		cin >> input; // "--<
		do
		{
			cin >> input;
			if (input == "r")
			{
				board[i]->push_back(new Hex(red));
				redPawnsNumber++;
				cin >> input;
			}
			else if (input == "b")
			{
				board[i]->push_back(new Hex(blue));
				bluePawnsNumber++;
				cin >> input;
			}
			else
			{
				board[i]->push_back(new Hex(none));
			}
			i++;
		} while (input != ">--" && input != ">");
		i = 0;
	} while (input != ">");

	int k = 1;
	i = k;
	do
	{
		cin >> input; // "--<
		if (input != "---")
		{
			do
			{
				cin >> input;
				if (input == "r")
				{
					board[i]->push_back(new Hex(red));
					redPawnsNumber++;
					cin >> input;
				}
				else if (input == "b")
				{
					board[i]->push_back(new Hex(blue));
					bluePawnsNumber++;
					cin >> input;
				}
				else
				{
					board[i]->push_back(new Hex(none));
				}
				i++;
			} while (input != ">--" && input != "---");
			k++;
			i = k;
		}
	} while (input != "---");
	boardSize = board.size();
	if (redPawnsNumber == bluePawnsNumber || redPawnsNumber == bluePawnsNumber + 1)
	{
		isBoardCorrect = true;
	}
	else
	{
		isBoardCorrect = false;
	}
}

int HexBoard::GetBoardSize() const
{
	return boardSize;
}

int HexBoard::GetBluePawnsNumber() const
{
	return bluePawnsNumber;
}

int HexBoard::GetRedPawnsNumber() const
{
	return redPawnsNumber;
}

bool HexBoard::GetIsBoardCorrect() const
{
	return isBoardCorrect;
}
