#include "HexBoard.h"
#include <iostream>
#include <string>

using std::cin;
using std::string;

bool HexBoard::Dfs(int vec1Index, int vec2Index, Colour colour) const
{
	if (vec1Index < 0 || vec2Index < 0 || vec1Index >= board.size() || vec2Index >= board[vec1Index]->size())
	{
		return false;
	}
	if ((*board[vec1Index])[vec2Index]->GetVisited() || (*board[vec1Index])[vec2Index]->GetColour() != colour)
	{
		return false;
	}
	else if (vec1Index + 1 >= board.size() && colour == red || vec2Index + 1 >= board[vec1Index]->size() && colour == blue)
	{
		if ((*board[vec1Index])[vec2Index]->GetColour() == colour)
		{
			(*board[vec1Index])[vec2Index]->SetVisited(true);
			return true;
		}
	}
	(*board[vec1Index])[vec2Index]->SetVisited(true);
	if (Dfs(vec1Index, vec2Index + 1, colour)) return true;
	if (Dfs(vec1Index + 1, vec2Index, colour)) return true;
	if (Dfs(vec1Index + 1, vec2Index + 1, colour)) return true;

	if (Dfs(vec1Index, vec2Index - 1, colour)) return true;
	if (Dfs(vec1Index - 1, vec2Index, colour)) return true;
	if (Dfs(vec1Index - 1, vec2Index - 1, colour)) return true;
	return false;
}

void HexBoard::ResetAllVisited() const
{
	for (int i = 0; i < GetBoardSize(); i++)
	{
		for (int k = 0; k < GetBoardSize(); k++)
		{
			(*board[i])[k]->SetVisited(false);
		}
	}
}

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
}

int HexBoard::GetBoardSize() const
{
	return board.size();
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
	if (redPawnsNumber == bluePawnsNumber || redPawnsNumber == bluePawnsNumber + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

EnumIsGameOver HexBoard::GetIsGameOver() const
{
	if (GetIsBoardCorrect())
	{
		for (int i = 0; i < GetBoardSize(); i++)
		{
			ResetAllVisited();
			if (Dfs(i, 0, blue))
			{
				return yes_blue;
			}
			ResetAllVisited();
			if (Dfs(0, i, red))
			{
				return yes_red;
			}
		}
	}
	return no;
}

HexBoard::~HexBoard()
{
	for (int i = 0; i < GetBoardSize(); i++)
	{
		for (int k = 0; k < GetBoardSize(); k++)
		{
			delete (*board[i])[k];
		}
		delete board[i];
	}
}
