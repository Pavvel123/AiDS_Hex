#include <iostream>
#include <string>
#include "HexBoard.h"

int main()
{
	std::string input;
	while (std::cin >> input)
	{
		HexBoard* board = new HexBoard();
		std::cin >> input;
		if (input == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT")
		{
			std::cout << (board->CanRed1Perfect() ? "YES\n" : "NO\n");
			std::cin >> input;
			std::cout << (board->CanBlue1Perfect() ? "YES\n" : "NO\n");
			std::cin >> input;
			std::cout << (board->CanRed2Perfect() ? "YES\n" : "NO\n");
			std::cin >> input;
			std::cout << (board->CanBlue2Perfect() ? "YES" : "NO");
		}
		else if (input == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
		{
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
			std::cout << board->GetBoardSize();
		}
		else if (input == "PAWNS_NUMBER")
		{
			std::cout << board->GetRedPawnsNumber() + board->GetBluePawnsNumber();
		}
		else if (input == "IS_BOARD_CORRECT")
		{
			std::cout << (board->IsBoardCorrect() ? "YES" : "NO");
		}
		else if (input == "IS_GAME_OVER")
		{
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
			std::cout << (board->IsBoardPossible() ? "YES" : "NO");
		}
		delete board;
		std::cout << "\n\n";
	}

	return 0;
}