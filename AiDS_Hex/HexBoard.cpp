#include "HexBoard.h"
#include <iostream>
#include <string>

using std::cin;
using std::string;

bool HexBoard::Dfs(int vec1Index, int vec2Index, Colour colour)
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
	if (Dfs(vec1Index, vec2Index + 1, colour))
	{
		return true;
	}
	if (Dfs(vec1Index + 1, vec2Index, colour))
	{
		return true;
	}
	if (Dfs(vec1Index + 1, vec2Index + 1, colour))
	{
		return true;
	}

	if (Dfs(vec1Index, vec2Index - 1, colour))
	{
		return true;
	}
	if (Dfs(vec1Index - 1, vec2Index, colour))
	{
		return true;
	}
	if (Dfs(vec1Index - 1, vec2Index - 1, colour))
	{
		return true;
	}
	return false;
}

void HexBoard::ResetAllVisited() const
{
	for (int i = 0; i < BoardSize(); i++)
	{
		for (int k = 0; k < BoardSize(); k++)
		{
			(*board[i])[k]->SetVisited(false);
		}
	}
}

Colour HexBoard::NowTurn() const
{
	if (redPawnsNumber == bluePawnsNumber)
	{
		return red;
	}
	return blue;
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

int HexBoard::GetBluePawnsNumber() const
{
	return bluePawnsNumber;
}

int HexBoard::GetRedPawnsNumber() const
{
	return redPawnsNumber;
}

int HexBoard::BoardSize() const
{
	return board.size();
}

bool HexBoard::IsBoardCorrect() const
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

EnumIsGameOver HexBoard::IsGameOver()
{
	if (IsBoardCorrect())
	{
		for (int i = 0; i < BoardSize(); i++)
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

bool HexBoard::IsBoardPossible()
{
	EnumIsGameOver isGameOver = IsGameOver();
	if (IsBoardCorrect() && (isGameOver == yes_blue && NowTurn() == red || isGameOver == yes_red && NowTurn() == blue || isGameOver == no))
	{
		if (isGameOver != no)
		{
			Colour colour;
			if (isGameOver == yes_red)
			{
				colour = red;
			}
			else
			{
				colour = blue;
			}

			for (int i = 0; i < BoardSize(); i++)
			{
				for (int k = 0; k < BoardSize(); k++)
				{
					if ((*board[i])[k]->GetColour() == colour)
					{
						(*board[i])[k]->SetColour(none);
						if (IsGameOver() != isGameOver)
						{
							return true;
						}
						(*board[i])[k]->SetColour(colour);
					}
				}
			}
			return false;
		}
		return true;
	}
	return false;
}

HexBoard::~HexBoard()
{
	for (int i = 0; i < BoardSize(); i++)
	{
		for (int k = 0; k < BoardSize(); k++)
		{
			delete (*board[i])[k];
		}
		delete board[i];
	}
}
