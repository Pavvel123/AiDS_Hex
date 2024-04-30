#include "HexBoard.h"
#include <iostream>
#include <string>

bool HexBoard::Dfs(int vec1Index, int vec2Index, Colour colour)
{
	if (vec1Index < 0 || vec2Index < 0 || vec1Index >= boardSize || vec2Index >= boardSize)
	{
		return false;
	}
	if (board[vec1Index][vec2Index].GetVisited() || board[vec1Index][vec2Index].GetColour() != colour)
	{
		return false;
	}
	else if (vec1Index + 1 >= boardSize && colour == red || vec2Index + 1 >= boardSize && colour == blue)
	{
		if (board[vec1Index][vec2Index].GetColour() == colour)
		{
			//(*board[vec1Index])[vec2Index]->SetVisited(true);
			return true;
		}
	}
	board[vec1Index][vec2Index].SetVisited(true);
	if (Dfs(vec1Index, vec2Index + 1, colour)) return true;
	if (Dfs(vec1Index + 1, vec2Index, colour)) return true;
	if (Dfs(vec1Index + 1, vec2Index + 1, colour)) return true;

	if (Dfs(vec1Index, vec2Index - 1, colour)) return true;
	if (Dfs(vec1Index - 1, vec2Index, colour)) return true;
	if (Dfs(vec1Index - 1, vec2Index - 1, colour)) return true;
	return false;
}

void HexBoard::ResetAllVisited()
{
	
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			board[i][k].SetVisited(false);
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
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (IsGameOver(red) == yes_red)
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
					return true;
				}
				board[i][k].SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanRed1NaiveStartBlue()
{
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
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (IsGameOver(blue) == yes_blue)
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
					return true;
				}
				board[i][k].SetColour(none);
				bluePawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanBlue1NaiveStartRed()
{
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
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (!IsGameOver() && CanRed1NaiveStartBlue())
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
					return true;
				}
				board[i][k].SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanRed2NaiveStartBlue()
{
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
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (!IsGameOver() && CanBlue1NaiveStartRed())
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
					return true;
				}
				board[i][k].SetColour(none);
				bluePawnsNumber--;
			}
		}
	}
	return false;
}


bool HexBoard::CanRed1PerfectStartRed()
{
	if (CanRed1NaiveStartRed()) return true;
	else return false;
}

bool HexBoard::CanRed1PerfectStartBlue()
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (IsGameOver(blue) == yes_blue)
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
					return false;
				}
				board[i][k].SetColour(none);
				bluePawnsNumber--;
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (IsGameOver(red) == yes_red)
				{
					board[i][k].SetColour(blue);
					redPawnsNumber--;
					bluePawnsNumber++;
					if (!CanRed1PerfectStartRed())
					{
						board[i][k].SetColour(none);
						bluePawnsNumber--;
						return false;
					}
					board[i][k].SetColour(none);
					bluePawnsNumber--;
				}
				else
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
				}
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (!CanRed1PerfectStartRed())
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
					return false;
				}
				board[i][k].SetColour(none);
				bluePawnsNumber--;
			}
		}
	}

	return true;
}

bool HexBoard::CanBlue1PerfectStartBlue()
{
	if (CanBlue1NaiveStartBlue()) return true;
	else return false;
}

bool HexBoard::CanBlue1PerfectStartRed()
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (IsGameOver(red) == yes_red)
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
					return false;
				}
				board[i][k].SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (IsGameOver(blue) == yes_blue)
				{
					board[i][k].SetColour(red);
					bluePawnsNumber--;
					redPawnsNumber++;
					if (!CanBlue1PerfectStartBlue())
					{
						board[i][k].SetColour(none);
						redPawnsNumber--;
						return false;
					}
					board[i][k].SetColour(none);
					redPawnsNumber--;
				}
				else
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
				}
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (!CanBlue1PerfectStartBlue())
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
					return false;
				}
				board[i][k].SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	return true;
}

bool HexBoard::CanRed2PerfectStartRed()
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (IsGameOver(red) == no && CanRed1PerfectStartBlue())
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
					return true;
				}
				board[i][k].SetColour(none);
				redPawnsNumber--;
			}
		}
	}
	return false;
}

bool HexBoard::CanRed2PerfectStartBlue()
{
	if (CanBlue1PerfectStartBlue()) return false;
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (IsGameOver(red) == yes_red)
				{
					board[i][k].SetColour(blue);
					redPawnsNumber--;
					bluePawnsNumber++;
					if (!CanRed2PerfectStartRed())
					{
						board[i][k].SetColour(none);
						bluePawnsNumber--;
						return false;
					}
					board[i][k].SetColour(none);
					bluePawnsNumber--;
				}
				else
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
				}
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (!CanRed2PerfectStartRed())
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
					return false;
				}
				board[i][k].SetColour(none);
				bluePawnsNumber--;
			}
		}
	}

	return true;
}

bool HexBoard::CanBlue2PerfectStartRed()
{
	if (CanRed1PerfectStartRed()) return false;
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (IsGameOver(blue) == yes_blue)
				{
					board[i][k].SetColour(red);
					bluePawnsNumber--;
					redPawnsNumber++;
					if (!CanBlue2PerfectStartBlue())
					{
						board[i][k].SetColour(none);
						redPawnsNumber--;
						return false;
					}
					board[i][k].SetColour(none);
					redPawnsNumber--;
				}
				else
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
				}
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				if (!CanBlue2PerfectStartBlue())
				{
					board[i][k].SetColour(none);
					redPawnsNumber--;
					return false;
				}
				board[i][k].SetColour(none);
				redPawnsNumber--;
			}
		}
	}

	return true;
}

bool HexBoard::CanBlue2PerfectStartBlue()
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				if (IsGameOver(blue) == no && CanBlue1PerfectStartRed())
				{
					board[i][k].SetColour(none);
					bluePawnsNumber--;
					return true;
				}
				board[i][k].SetColour(none);
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
	int i = 0;
	int k = 0;
	do
	{
		std::cin >> input; // "--<
		do
		{
			std::cin >> input;
			if (input == "r")
			{
				board[i][k].SetColour(red);
				redPawnsNumber++;
				std::cin >> input;
			}
			else if (input == "b")
			{
				board[i][k].SetColour(blue);
				bluePawnsNumber++;
				std::cin >> input;
			}
			else
			{
				board[i][k].SetColour(none);
			}
			i++;
			k--;
		} while (k >= 0);//input != ">--" && input != ">");
		k = i;
		i = 0;
	} while (input != ">");

	boardSize = k;
	k--;
	int r = 1;
	i = r;
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
					board[i][k].SetColour(red);
					redPawnsNumber++;
					std::cin >> input;
				}
				else if (input == "b")
				{
					board[i][k].SetColour(blue);
					bluePawnsNumber++;
					std::cin >> input;
				}
				else
				{
					board[i][k].SetColour(none);
				}
				i++;
				k--;
			} while (k - r >= 0);//input != ">--" && input != "---");
			r++;
			k = boardSize - 1;
			i = r;
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

int HexBoard::GetBoardSize() const
{
	return boardSize;
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
		
		for (int i = 0; i < boardSize; i++)
		{
			if ((col == blue || col == none) && board[i][0].GetColour() == blue)
			{
				ResetAllVisited();
				if (Dfs(i, 0, blue))
				{
					return yes_blue;
				}
			}
			if ((col == red || col == none) && board[0][i].GetColour() == red)
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

			
			for (int i = 0; i < boardSize; i++)
			{
				for (int k = 0; k < boardSize; k++)
				{
					if (board[i][k].GetColour() == colour)
					{
						board[i][k].SetColour(none);
						if (IsGameOver() != isGameOver)
						{
							return true;
						}
						board[i][k].SetColour(colour);
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
	if (redPawnsNumber + 1 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
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
	if (bluePawnsNumber + 1 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
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
	if (redPawnsNumber + 2 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
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
	if (bluePawnsNumber + 2 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
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


bool HexBoard::CanRed1Perfect()
{
	if (redPawnsNumber + 1 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == red)
		{
			if (CanRed1PerfectStartRed()) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanRed1PerfectStartBlue()) return true;
			else return false;
		}
	}
	return false;
}

bool HexBoard::CanBlue1Perfect()
{
	if (bluePawnsNumber + 1 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == blue)
		{
			if (CanBlue1PerfectStartBlue()) return true;
			else return false;
		}
		else //if (NowTurn() == red)
		{
			if (CanBlue1PerfectStartRed()) return true;
			else return false;
		}
	}
	return false;
}

bool HexBoard::CanRed2Perfect()
{
	if (redPawnsNumber + 2 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == red)
		{
			if (CanRed2PerfectStartRed()) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanRed2PerfectStartBlue()) return true;
			else return false;
		}
	}
	return false;
}

bool HexBoard::CanBlue2Perfect()
{
	if (bluePawnsNumber + 2 >= boardSize && IsBoardCorrect() && IsGameOver() == no)
	{
		if (NowTurn() == red)
		{
			if (CanBlue2PerfectStartRed()) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanBlue2PerfectStartBlue()) return true;
			else return false;
		}
	}
	return false;
}

HexBoard::~HexBoard()
{
}
