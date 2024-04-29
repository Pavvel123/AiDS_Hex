#include "HexBoard.h"
#include <iostream>
#include <string>

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
			//(*board[vec1Index])[vec2Index]->SetVisited(true);
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

void HexBoard::ResetAllVisited()
{
	int boardSize = BoardSize();
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
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

bool HexBoard::CanRed1NaiveStartRed()
{
	int boardSize = BoardSize();
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if ((*board[i])[k]->GetColour() == none)
			{
				(*board[i])[k]->SetColour(red);
				redPawnsNumber++;
				if (IsGameOver(red) == yes_red)
				{
					(*board[i])[k]->SetColour(none);
					redPawnsNumber--;
					return true;
				}
				(*board[i])[k]->SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanRed1NaiveStartBlue()
{
	int boardSize = BoardSize();
	bluePawnsNumber++;
	if (bluePawnsNumber + redPawnsNumber + 1 <= boardSize * boardSize && CanRed1NaiveStartRed())
	{
		bluePawnsNumber--;
		return true;
	}
	bluePawnsNumber--;
	return false;
}

bool HexBoard::CanBlue1NaiveStartBlue()
{
	int boardSize = BoardSize();
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if ((*board[i])[k]->GetColour() == none)
			{
				(*board[i])[k]->SetColour(blue);
				bluePawnsNumber++;
				if (IsGameOver(blue) == yes_blue)
				{
					(*board[i])[k]->SetColour(none);
					bluePawnsNumber--;
					return true;
				}
				(*board[i])[k]->SetColour(none);
				bluePawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanBlue1NaiveStartRed()
{
	int boardSize = BoardSize();
	redPawnsNumber++;
	if (bluePawnsNumber + redPawnsNumber + 1 <= boardSize * boardSize && CanBlue1NaiveStartBlue())
	{
		redPawnsNumber--;
		return true;
	}
	redPawnsNumber--;
	return false;
}

bool HexBoard::CanRed2NaiveStartRed()
{
	int boardSize = BoardSize();
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if ((*board[i])[k]->GetColour() == none)
			{
				(*board[i])[k]->SetColour(red);
				redPawnsNumber++;
				if (CanRed1NaiveStartBlue())
				{
					(*board[i])[k]->SetColour(none);
					redPawnsNumber--;
					return true;
				}
				(*board[i])[k]->SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanRed2NaiveStartBlue()
{
	int boardSize = BoardSize();
	bluePawnsNumber++;
	if (bluePawnsNumber + redPawnsNumber + 3 <= boardSize * boardSize && CanRed2NaiveStartRed())
	{
		bluePawnsNumber--;
		return true;
	}
	bluePawnsNumber--;
	return false;
}

bool HexBoard::CanBlue2NaiveStartRed()
{
	int boardSize = BoardSize();
	redPawnsNumber++;
	if (bluePawnsNumber + redPawnsNumber + 3 <= boardSize * boardSize && CanBlue2NaiveStartBlue())
	{
		redPawnsNumber--;
		return true;
	}
	redPawnsNumber--;
	return false;
}

bool HexBoard::CanBlue2NaiveStartBlue()
{
	int boardSize = BoardSize();
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if ((*board[i])[k]->GetColour() == none)
			{
				(*board[i])[k]->SetColour(blue);
				bluePawnsNumber++;
				if (CanBlue1NaiveStartRed())
				{
					(*board[i])[k]->SetColour(none);
					bluePawnsNumber--;
					return true;
				}
				(*board[i])[k]->SetColour(none);
				bluePawnsNumber--;
			}
		}
	}
	return false;
}

HexBoard::HexBoard()
{
	redPawnsNumber = 0;
	bluePawnsNumber = 0;
	std::string input;
	std::cin >> input; // "---"
	int i = 0;
	do
	{
		board.push_back(new std::vector<Hex*>());
		std::cin >> input; // "--<
		do
		{
			std::cin >> input;
			if (input == "r")
			{
				board[i]->push_back(new Hex(red));
				redPawnsNumber++;
				std::cin >> input;
			}
			else if (input == "b")
			{
				board[i]->push_back(new Hex(blue));
				bluePawnsNumber++;
				std::cin >> input;
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
		std::cin >> input; // "--<
		if (input != "---")
		{
			do
			{
				std::cin >> input;
				if (input == "r")
				{
					board[i]->push_back(new Hex(red));
					redPawnsNumber++;
					std::cin >> input;
				}
				else if (input == "b")
				{
					board[i]->push_back(new Hex(blue));
					bluePawnsNumber++;
					std::cin >> input;
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

EnumIsGameOver HexBoard::IsGameOver(Colour col)
{
	if (IsBoardCorrect())
	{
		int boardSize = BoardSize();
		for (int i = 0; i < boardSize; i++)
		{
			if ((col == blue || col == none) && (*board[i])[0]->GetColour() == blue)
			{
				ResetAllVisited();
				if (Dfs(i, 0, blue))
				{
					return yes_blue;
				}
			}
			if ((col == red || col == none) && (*board[0])[i]->GetColour() == red)
			{
				ResetAllVisited();
				if (Dfs(0, i, red))
				{
					return yes_red;
				}
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

			int boardSize = BoardSize();
			for (int i = 0; i < boardSize; i++)
			{
				for (int k = 0; k < boardSize; k++)
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

bool HexBoard::CanRed1Naive()
{
	if (redPawnsNumber + 1 >= BoardSize() && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == red)
		{
			if (CanRed1NaiveStartRed()) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanRed1NaiveStartBlue()) return true;
			else return false;
		}
	}
	return false;
}

bool HexBoard::CanBlue1Naive()
{
	if (bluePawnsNumber + 1 >= BoardSize() && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == blue)
		{
			if (CanBlue1NaiveStartBlue()) return true;
			else return false;
		}
		else //if (NowTurn() == red)
		{
			if (CanBlue1NaiveStartRed()) return true;
			else return false;
		}
	}
	return false;
}

bool HexBoard::CanRed2Naive()
{
	if (redPawnsNumber + 2 >= BoardSize() && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == red)
		{
			if (CanRed2NaiveStartRed()) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanRed2NaiveStartBlue()) return true;
			else return false;
		}
	}
	return false;
}

bool HexBoard::CanBlue2Naive()
{
	if (bluePawnsNumber + 2 >= BoardSize() && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == red)
		{
			if (CanBlue2NaiveStartRed()) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanBlue2NaiveStartBlue()) return true;
			else return false;
		}
	}
	return false;
}

HexBoard::~HexBoard()
{
	int boardSize = BoardSize();
	for (int i = boardSize - 1; i >= 0; i--)
	{
		for (int k = boardSize - 1; k >= 0; k--)
		{
			delete (*board[i])[k];
			(*board[i]).erase((*board[i]).begin() + k);
		}
		delete board[i];
		board.erase(board.begin() + i);
	}
}
