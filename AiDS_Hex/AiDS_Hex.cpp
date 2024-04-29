#include <iostream>
#include <string>
#include "HexBoard.h"

int main()
{
	int size = 1;
	for (int i = 0; i < size; i++)
	{
		std::string input;
		HexBoard* board = new HexBoard();
		std::cin >> input;
		if (input == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
		{
			size = 1206;
			std::cout << (board->CanRed1Naive() ? "YES\n" : "NO\n");
			std::cin >> input;
			std::cout << (board->CanBlue1Naive() ? "YES\n" : "NO\n");
			std::cin >> input;
			std::cout << (board->CanRed2Naive() ? "YES\n" : "NO\n");
			std::cin >> input;
			std::cout << (board->CanBlue2Naive() ? "YES" : "NO");
		}
		else if (input == "BOARD_SIZE")
		{
			size = 517;
			std::cout << board->BoardSize();
		}
		else if (input == "PAWNS_NUMBER")
		{
			size = 517;
			std::cout << board->GetRedPawnsNumber() + board->GetBluePawnsNumber();
		}
		else if (input == "IS_BOARD_CORRECT")
		{
			size = 517;
			std::cout << (board->IsBoardCorrect() ? "YES" : "NO");
		}
		else if (input == "IS_GAME_OVER")
		{
			size = 1034;
			switch (board->IsGameOver())
			{
			case no:
				std::cout << "NO";
				break;
			case yes_red:
				std::cout << "YES RED";
				break;
			case yes_blue:
				std::cout << "YES BLUE";
				break;
			}
		}
		else if (input == "IS_BOARD_POSSIBLE")
		{
			size = 1017;
			std::cout << (board->IsBoardPossible() ? "YES" : "NO");
		}
		
		delete board;
		std::cout << "\n\n";
	}

	return 0;
}