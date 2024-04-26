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
	int size = 10;
	string input = "";
	HexBoard* board = nullptr;
	for (int i = 0; i < size; i++)
	{
		board = new HexBoard();
		cin >> input;
		if (input == "BOARD_SIZE")
		{
			size = 517;
			cout << board->GetBoardSize();
		}
		else if (input == "PAWNS_NUMBER")
		{
			size = 517;
			cout << board->GetRedPawnsNumber() + board->GetBluePawnsNumber();
		}
		else if (input == "IS_BOARD_CORRECT")
		{
			size = 517;
			cout << (board->GetIsBoardCorrect() ? "YES" : "NO");
		}
		else if (input == "IS_GAME_OVER")
		{
			size = 1034;
			switch (board->GetIsGameOver())
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
		delete board;
		cout << endl << endl;
	}

	return 0;
}

/*
		  ---
	   --< b >--
	--<   >-< r >--
 --< b >-< r >-< b >--
< b >-< r >-< b >-< r >
 --<   >-< b >-< r >--
	--< r >-< r >--
	   --< b >--
		  ---
IS_GAME_OVER

*/