#pragma once
#include <vector>
#include "Hex.h"

using std::vector;

class HexBoard
{
private:
	vector<vector<Hex*>*> board;
	int boardSize;
	int bluePawnsNumber;
	int redPawnsNumber;
	bool isBoardCorrect;

public:
	HexBoard();
	int GetBoardSize() const;
	int GetBluePawnsNumber() const;
	int GetRedPawnsNumber() const;
	bool GetIsBoardCorrect() const;
};