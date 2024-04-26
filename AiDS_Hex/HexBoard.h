#pragma once
#include <vector>
#include "Hex.h"

using std::vector;

enum EnumIsGameOver
{
	no,
	yes_red,
	yes_blue
};

class HexBoard
{
private:
	vector<vector<Hex*>*> board;
	int bluePawnsNumber;
	int redPawnsNumber;
	bool Dfs(int vec1Index, int vec2Index, Colour colour) const;
	void ResetAllVisited() const;

public:
	HexBoard();
	int GetBoardSize() const;
	int GetBluePawnsNumber() const;
	int GetRedPawnsNumber() const;
	bool GetIsBoardCorrect() const;
	EnumIsGameOver GetIsGameOver() const;
	~HexBoard();
};