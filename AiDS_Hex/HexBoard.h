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
	bool Dfs(int vec1Index, int vec2Index, Colour colour);
	void ResetAllVisited() const;
	Colour NowTurn() const;

public:
	HexBoard();
	int GetBluePawnsNumber() const;
	int GetRedPawnsNumber() const;
	int BoardSize() const;
	bool IsBoardCorrect() const;
	EnumIsGameOver IsGameOver();
	bool IsBoardPossible();
	~HexBoard();
};