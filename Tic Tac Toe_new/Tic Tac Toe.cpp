#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include "ttt_structs.h"


bool playAgain()
{
	while (true)
	{
		std::cout << "Play again? (y/n): ";
		char option{};

		std::cin >> option;

		switch (option)
		{
		case 'y':
		case 'Y':
			return true;
			break;
		case 'n':
		case 'N':
			return false;
			break;
		default:
			break;
		}
	}
}

Players playGame(Board& board)
{
	Players winner{ Players::noPlayer };
	int turn{ 1 };

	for (; winner == Players::noPlayer && turn <= (maxColumns * maxRows); turn++)
	{
		board.print();
		if (turn % 2 != 0)
			board.markSquare(Players::player1);
		else
			board.markSquare(Players::player2);

		winner = board.checkForWin();
	}

	return winner;
}

int main()
{
	do {
		Board gameBoard{};

		Players winner{ playGame(gameBoard) };

		if (winner != Players::noPlayer)
			std::cout << getPlayerName(winner) << " wins!\n";
		else
			std::cout << "It's a draw!";

		std::cout << "\n\n";

		gameBoard.print();
	} while (playAgain());


	return 0;
}