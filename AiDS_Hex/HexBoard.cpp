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

bool HexBoard::CanColour1StartSame(Colour colour)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(colour);
				colour == red ? redPawnsNumber++ : bluePawnsNumber++;
				bool cond1 = IsGameOver(colour) == (colour == red ? yes_red : yes_blue);
				board[i][k].SetColour(none);
				colour == red ? redPawnsNumber-- : bluePawnsNumber--;
				if (cond1) return true;
			}
		}
	}
	return false;
}


bool HexBoard::CanColour1NaiveStartOpposite(Colour colour)
{
	colour == red ? bluePawnsNumber++ : redPawnsNumber++;
	bool cond1 = bluePawnsNumber + redPawnsNumber + 1 <= boardSize * boardSize && CanColour1StartSame(colour);
	colour == red ? bluePawnsNumber-- : redPawnsNumber--;
	if (cond1) return true;
	else return false;
}

bool HexBoard::CanColour2NaiveStartSame(Colour colour)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(colour);
				colour == red ? redPawnsNumber++ : bluePawnsNumber++;
				bool cond1 = !IsGameOver() && CanColour1NaiveStartOpposite(colour);
				board[i][k].SetColour(none);
				colour == red ? redPawnsNumber-- : bluePawnsNumber--;
				if (cond1) return true;
			}
		}
	}
	return false;
}

bool HexBoard::CanColour2NaiveStartOpposite(Colour colour)
{
	colour == red ? bluePawnsNumber++ : redPawnsNumber++;
	bool cond1 = bluePawnsNumber + redPawnsNumber + 3 <= boardSize * boardSize && CanColour2NaiveStartSame(colour);
	colour == red ? bluePawnsNumber-- : redPawnsNumber--;
	if (cond1) return true;
	else return false;
}


bool HexBoard::CanColour1PerfectStartOpposite(Colour colour)
{
	Colour oppositeColour = colour == red ? blue : red;
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(oppositeColour);
				oppositeColour == blue ? bluePawnsNumber++ : redPawnsNumber++;
				bool cond1 = IsGameOver(oppositeColour) == (oppositeColour == blue ? yes_blue : yes_red);
				board[i][k].SetColour(none);
				oppositeColour == blue ? bluePawnsNumber-- : redPawnsNumber--;
				if (cond1) return false;
			}
		}
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(colour);
				colour == red ? redPawnsNumber++ : bluePawnsNumber++;
				bool cond1 = IsGameOver(colour) == (colour == red ? yes_red : yes_blue);
				board[i][k].SetColour(none);
				colour == red ? redPawnsNumber-- : bluePawnsNumber--;
				if (cond1)
				{
					board[i][k].SetColour(oppositeColour);
					oppositeColour == blue ? bluePawnsNumber++ : redPawnsNumber++;
					bool cond2 = !CanColour1StartSame(colour);
					board[i][k].SetColour(none);
					oppositeColour == blue ? bluePawnsNumber-- : redPawnsNumber--;
					if (cond2) return false;
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
				board[i][k].SetColour(oppositeColour);
				oppositeColour == blue ? bluePawnsNumber++ : redPawnsNumber++;
				bool cond1 = !CanColour1StartSame(colour);
				board[i][k].SetColour(none);
				oppositeColour == blue ? bluePawnsNumber-- : redPawnsNumber--;
				if (cond1) return false;
			}
		}
	}

	return true;
}

bool HexBoard::CanColour2PerfectStartSame(Colour colour)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(colour);
				colour == red ? redPawnsNumber++ : bluePawnsNumber++;
				bool cond1 = IsGameOver(colour) == no && CanColour1PerfectStartOpposite(colour);
				board[i][k].SetColour(none);
				colour == red ? redPawnsNumber-- : bluePawnsNumber--;
				if (cond1) return true;
			}
		}
	}
	return false;
}

bool HexBoard::CanColour2PerfectStartOpposite(Colour colour)
{
	Colour oppositeColour = (colour == red ? blue : red);
	if (CanColour1StartSame(oppositeColour)) return false;
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			if (board[i][k].GetColour() == none)
			{
				board[i][k].SetColour(colour);
				colour == red ? redPawnsNumber++ : bluePawnsNumber++;
				bool cond1 = IsGameOver(colour) == (colour == red ? yes_red : yes_blue);
				board[i][k].SetColour(none);
				colour == red ? redPawnsNumber-- : bluePawnsNumber--;
				if (cond1)
				{
					board[i][k].SetColour(oppositeColour);
					oppositeColour == blue ? bluePawnsNumber++ : redPawnsNumber++;
					bool cond2 = !CanColour2PerfectStartSame(colour);
					board[i][k].SetColour(none);
					oppositeColour == blue ? bluePawnsNumber-- : redPawnsNumber--;
					if (cond2) return false;
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
				board[i][k].SetColour(oppositeColour);
				oppositeColour == blue ? bluePawnsNumber++ : redPawnsNumber++;
				bool cond1 = !CanColour2PerfectStartSame(colour);
				board[i][k].SetColour(none);
				oppositeColour == blue ? bluePawnsNumber-- : redPawnsNumber--;
				if (cond1) return false;
			}
		}
	}

	return true;
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
			if (CanColour1StartSame(red)) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanColour1NaiveStartOpposite(red)) return true;
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
			if (CanColour1StartSame(blue)) return true;
			else return false;
		}
		else //if (NowTurn() == red)
		{
			if (CanColour1NaiveStartOpposite(blue)) return true;
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
			if (CanColour2NaiveStartSame(red)) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanColour2NaiveStartOpposite(red)) return true;
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
			if (CanColour2NaiveStartOpposite(blue)) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanColour2NaiveStartSame(blue)) return true;
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
			if (CanColour1StartSame(red)) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanColour1PerfectStartOpposite(red)) return true;
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
			if (CanColour1StartSame(blue)) return true;
			else return false;
		}
		else //if (NowTurn() == red)
		{
			if (CanColour1PerfectStartOpposite(blue)) return true;
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
			if (CanColour2PerfectStartSame(red)) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanColour2PerfectStartOpposite(red)) return true;
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
			if (CanColour2PerfectStartOpposite(blue)) return true;
			else return false;
		}
		else //if (NowTurn() == blue)
		{
			if (CanColour2PerfectStartSame(blue)) return true;
			else return false;
		}
	}
	return false;
}

HexBoard::~HexBoard()
{
}
