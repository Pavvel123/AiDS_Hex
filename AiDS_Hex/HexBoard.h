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

	bool CanColour1StartSame(Colour colour);

	bool CanColour1NaiveStartOpposite(Colour colour);
	bool CanColour2NaiveStartSame(Colour colour);
	bool CanColour2NaiveStartOpposite(Colour colour);

	bool CanColour1PerfectStartOpposite(Colour colour);
	bool CanColour2PerfectStartSame(Colour colour);
	bool CanColour2PerfectStartOpposite(Colour colour);

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

	bool CanRed1Perfect();
	bool CanBlue1Perfect();
	bool CanRed2Perfect();
	bool CanBlue2Perfect();
	~HexBoard();
};