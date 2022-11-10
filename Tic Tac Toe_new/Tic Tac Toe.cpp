#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include "ttt_structs.h"


void printSquare(const Square& square)
{
	switch (square.status)
	{
	case (Players::noPlayer):
	{
		std::cout << "[ ]";
		return;
	}
	case (Players::player1):
	{
		std::cout << "[X]";
		return;
	}
	case (Players::player2):
	{
		std::cout << "[O]";
		return;
	}
	default:
	{
		std::cout << "[?]";
		return;
	}
	}

	return;
}

void printLine(const Line& line)
{
	for (int i{ 0 }; i < maxColumns; i++)
	{
		printSquare(line.s[i]);
		std::cout << " ";
	}
}

void printBoard(const Board& board)
{
	for (int i{ 0 }; i < maxColumns; i++)
	{
		std::cout << alphabet[i] << "\t";
		printLine(board.l[i]);
		std::cout << "\n";
	}

	std::cout << "\t ";

	for (int i(0); i < maxRows; i++)
	{
		std::cout << (i + 1) << "   ";
	}

	std::cout << "\n\n";
}

Line makeTestLine()
{
	Line testLine{  };
	testLine.s[1].status = Players::player1;
	testLine.s[2].status = Players::player2;
	return testLine;
}

std::string getPlayerName(Players player)
{
	auto playerNum{ std::to_string(static_cast<int>(player)) };
	std::string playerName{ "Player " };
	playerName += playerNum;
	return playerName;
}

void markSquare(Board& board, Players player)
{
	while (true)
	{
		std::cout << getPlayerName(player) << ", enter a row (a - " << alphabet[(maxRows - 1)] << ") and column (1 - " << (maxColumns) << "): ";

		char rowInput{};
		std::cin >> rowInput;

		// Finds char in global alphabet array and returns index in int form (from 0 - 26)
		int row{ static_cast<int>(alphabet.find(rowInput)) };

		int columnInput{};
		std::cin >> columnInput;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (!std::cin) // if cin extraction fails
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		// Since arrays in C++ start at index 0, this decrements the input to fit the line array
		--columnInput;

		if (columnInput >= maxColumns || columnInput < 0)
			std::cout << "Invalid column, please enter a column between 1 and " << maxColumns << ".\n";
		else if (row == -1 || row >= maxRows)
			std::cout << "Invalid row, please enter a row between a and " << alphabet[(maxRows - 1)] << ".\n";
		else if (board.l[row].s[columnInput].status != Players::noPlayer)
			std::cout << "This square has already been marked by " << getPlayerName(board.l[row].s[columnInput].status) << "!\n";
		else {
			board.l[row].s[columnInput].status = player;
			return;
		}

	}

}

Players checkForLineFill(const Line& line)
{
	bool fill{ true };
	Players currentPlayerFill{ line.s[0].status };
	for (int i{ 0 }; i < maxColumns && fill; i++)
	{
		if (line.s[i].status == Players::noPlayer || line.s[i].status != currentPlayerFill)
			fill = false;
	}

	if (fill)
		return currentPlayerFill;
	else
		return Players::noPlayer;
}

Players verticalLineCheck(const Board& board)
{
	for (int i{ 0 }; i < maxColumns; i++)
	{
		// Create a temporary Line to check for fills
		Line tempLine{};

		// Fill temporary line with vertical squares on Board, row by row downwards
		for (int n{ 0 }; n < maxRows; n++)
		{
			tempLine.s[n].status = board.l[n].s[i].status;
		}

		// Returns with the player who filled up the line if one was found
		Players winCheck{ checkForLineFill(tempLine) };
		if (winCheck != Players::noPlayer)
			return winCheck;
	}

	// If no player has filled up a vertical line, returns noPlayer
	return Players::noPlayer;
}

Players diagonalLineCheck(Board board)
{
	for (int i{ 0 }; i < maxColumns && i < maxRows; i++)
	{
		// Create a temporary Line to check for fills
		Line tempLine{};

		// Fill temporary line with diagonal squares on Board
		// Tests for diagonal #1 (starts at top left, goes to bottom right)
		for (int n{ 0 }; n < maxRows; n++)
		{
			tempLine.s[n].status = board.l[n].s[n].status;
		}

		Players winCheck{ checkForLineFill(tempLine) };
		if (winCheck != Players::noPlayer)
			return winCheck;

		// Tests for diagonal #2 (starts at top right, goes to bottom left)
		int x{ maxRows - 1 };

		for (int n{ 0 }; n < maxRows; n++, x--)
		{
			tempLine.s[n].status = board.l[n].s[x].status;
		}

		winCheck = checkForLineFill(tempLine);
		if (winCheck != Players::noPlayer)
			return winCheck;

	}

	return Players::noPlayer;

}

Players checkForWin(const Board& board)
{
	// Check for horizontal fills
	for (int i{ 0 }; i < maxRows; i++)
	{
		Players winCheck{ checkForLineFill(board.l[i]) };
		if (winCheck != Players::noPlayer)
			return winCheck;
	}

	// Check for vertical or diagonal fills; if none found, returns noPlayer
	Players winCheck{};
	if ((winCheck = verticalLineCheck(board)) != Players::noPlayer)
		return winCheck;
	else if ((winCheck = diagonalLineCheck(board)) != Players::noPlayer)
		return winCheck;
	else
		return Players::noPlayer;

}

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

Players playGame(Board board)
{
	Players winner{ Players::noPlayer };
	int turn{ 1 };

	for (; winner == Players::noPlayer && turn <= (maxColumns * maxRows); turn++)
	{
		printBoard(board);
		if (turn % 2 != 0)
			markSquare(board, Players::player1);
		else
			markSquare(board, Players::player2);

		winner = checkForWin(board);
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

		printBoard(gameBoard);
	} while (playAgain());


	return 0;
}