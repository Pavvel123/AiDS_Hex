#pragma once
#include <vector>
#include "Hex.h"

class Hex;

enum EnumIsGameOver
{
	no,
	yes_red,
	yes_blue
};

class HexBoard
{
private:
	Hex board[11][11];
	int bluePawnsNumber;
	int redPawnsNumber;
	int boardSize;
	bool Dfs(int vec1Index, int vec2Index, Colour colour);
	void ResetAllVisited();
	Colour NowTurn() const;
	bool CanRed1NaiveStartRed();
	bool CanRed1NaiveStartBlue();
	bool CanBlue1NaiveStartBlue();
	bool CanBlue1NaiveStartRed();
	bool CanRed2NaiveStartRed();
	bool CanRed2NaiveStartBlue();
	bool CanBlue2NaiveStartRed();
	bool CanBlue2NaiveStartBlue();

public:
	HexBoard();
	int GetBluePawnsNumber() const;
	int GetRedPawnsNumber() const;
	int GetBoardSize() const;
	bool IsBoardCorrect() const;
	EnumIsGameOver IsGameOver(Colour col = none);
	bool IsBoardPossible();
	bool CanRed1Naive();
	bool CanBlue1Naive();
	bool CanRed2Naive();
	bool CanBlue2Naive();
	~HexBoard();
};