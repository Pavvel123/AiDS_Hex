#include <iostream>
#include <string>
#include "HexBoard.h"
#define SIZE 517
#define SIZE1 1

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	string input = "";
	HexBoard* board = nullptr;
	for (int i = 0; i < SIZE; i++)
	{
		board = new HexBoard();
		cin >> input;
		if (input == "BOARD_SIZE")
		{
			cout << board->GetBoardSize();
		}
		else if (input == "PAWNS_NUMBER")
		{
			cout << board->GetRedPawnsNumber() + board->GetBluePawnsNumber();
		}
		else if (input == "IS_BOARD_CORRECT")
		{
			cout << (board->GetIsBoardCorrect() ? "YES" : "NO");
		}
		delete board;
		cout << endl << endl;
	}

	return 0;
}