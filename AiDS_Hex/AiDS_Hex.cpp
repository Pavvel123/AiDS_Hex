#include <iostream>
#include <string>
#include "HexBoard.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	int size = 1;
	string input = "";
	HexBoard* board = nullptr;
	for (int i = 0; i < size; i++)
	{
		board = new HexBoard();
		cin >> input;
		if (input == "BOARD_SIZE")
		{
			size = 517;
			cout << board->BoardSize();
		}
		else if (input == "PAWNS_NUMBER")
		{
			size = 517;
			cout << board->GetRedPawnsNumber() + board->GetBluePawnsNumber();
		}
		else if (input == "IS_BOARD_CORRECT")
		{
			size = 517;
			cout << (board->IsBoardCorrect() ? "YES" : "NO");
		}
		else if (input == "IS_GAME_OVER")
		{
			size = 1034;
			switch (board->IsGameOver())
			{
			case no:
				cout << "NO";
				break;
			case yes_red:
				cout << "YES RED";
				break;
			case yes_blue:
				cout << "YES BLUE";
				break;
			}
		}
		else if (input == "IS_BOARD_POSSIBLE")
		{
			size = 1017;
			cout << (board->IsBoardPossible() ? "YES" : "NO");
		}
		delete board;
		cout << endl << endl;
	}

	return 0;
}