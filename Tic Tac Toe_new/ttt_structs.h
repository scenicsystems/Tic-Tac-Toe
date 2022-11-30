#ifndef TTT_STRUCTS
#define TTT_STRUCTS
#include <string_view>
#include <iostream>


constexpr int maxRows{ 5 };
constexpr int maxColumns{ 5 };

constexpr std::string_view alphabet{ "abcdefghijklmnopqrstuvwxyz" };

enum class Players
{
	noPlayer,
	player1,
	player2,
};

std::string getPlayerName(Players player)
{
	auto playerNum{ std::to_string(static_cast<int>(player)) };
	std::string playerName{ "Player " };
	playerName += playerNum;
	return playerName;
}

class Square
{
private:
	Players m_status{ };

public:

	Square() : m_status{ Players::noPlayer }
	{

	}

	Players getStatus()
	{
		return m_status;
	}

	void setStatus(Players player)
	{
		std::cout << "\nDEBUG: before set, player status: " << getPlayerName(getStatus());
		m_status = player;
		std::cout << "\nDEBUG: after set, player status: " << getPlayerName(getStatus());
	}

	void print()
	{
		switch (m_status)
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

};

class Line
{
private:
	Square m_square[maxRows]{};

public:

	Line() : m_square{}
	{
	}

	Square getSquare(int squareNum)
	{
		return m_square[squareNum];
	}

	void print()
	{
		for (int i{ 0 }; i < maxColumns; i++)
		{
			m_square[i].print();
			std::cout << " ";
		}
	}

	Players checkForFill()
	{
		bool fill{ true };
		Players currentPlayerFill{ m_square[0].getStatus()};
		for (int i{ 0 }; i < maxColumns && fill; i++)
		{
			if (m_square[i].getStatus() == Players::noPlayer || m_square[i].getStatus() != currentPlayerFill)
				fill = false;
		}

		if (fill)
			return currentPlayerFill;
		else
			return Players::noPlayer;
	}

};



class Board
{
private:
	Line m_line[maxColumns]{};

public:

	void print()
	{
		for (int i{ 0 }; i < maxColumns; i++)
		{
			std::cout << alphabet[i] << "\t";
			m_line[i].print();
			std::cout << "\n";
		}

		std::cout << "\t ";

		for (int i(0); i < maxRows; i++)
		{
			std::cout << (i + 1) << "   ";
		}

		std::cout << "\n\n";
	}

	void markSquare(Players player)
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
			else if (m_line[row].getSquare(columnInput).getStatus() != Players::noPlayer)
				std::cout << "This square has already been marked by " << getPlayerName(m_line[row].getSquare(columnInput).getStatus()) << "!\n";
			else {
				m_line[row].getSquare(columnInput).setStatus(player);
				return;
			}

		}

	}

	Players verticalLineCheck()
	{
		for (int i{ 0 }; i < maxColumns; i++)
		{
			// Create a temporary Line to check for fills
			Line tempLine{};

			// Fill temporary line with vertical squares on Board, row by row downwards
			for (int n{ 0 }; n < maxRows; n++)
			{
				tempLine.getSquare(n).setStatus(m_line[n].getSquare(i).getStatus());
			}

			// Returns with the player who filled up the line if one was found
			Players winCheck{ tempLine.checkForFill()};
			if (winCheck != Players::noPlayer)
				return winCheck;
		}

		// If no player has filled up a vertical line, returns noPlayer
		return Players::noPlayer;
	}

	Players diagonalLineCheck()
	{
		for (int i{ 0 }; i < maxColumns && i < maxRows; i++)
		{
			// Create a temporary Line to check for fills
			Line tempLine{};

			// Fill temporary line with diagonal squares on Board
			// Tests for diagonal #1 (starts at top left, goes to bottom right)
			for (int n{ 0 }; n < maxRows; n++)
			{
				tempLine.getSquare(n).setStatus(m_line[n].getSquare(n).getStatus());
			}

			Players winCheck{ tempLine.checkForFill()};
			if (winCheck != Players::noPlayer)
				return winCheck;

			// Tests for diagonal #2 (starts at top right, goes to bottom left)
			int x{ maxRows - 1 };

			for (int n{ 0 }; n < maxRows; n++, x--)
			{
				tempLine.getSquare(n).setStatus(m_line[n].getSquare(x).getStatus());
			}

			winCheck = tempLine.checkForFill();
			if (winCheck != Players::noPlayer)
				return winCheck;

		}

		return Players::noPlayer;

	}

	Players checkForWin()
	{
		// Check for horizontal fills
		for (int i{ 0 }; i < maxRows; i++)
		{
			Players winCheck{ m_line[i].checkForFill()};
			if (winCheck != Players::noPlayer)
				return winCheck;
		}

		// Check for vertical or diagonal fills; if none found, returns noPlayer
		Players winCheck{};
		if ((winCheck = this->verticalLineCheck()) != Players::noPlayer)
			return winCheck;
		else if ((winCheck = this->diagonalLineCheck()) != Players::noPlayer)
			return winCheck;
		else
			return Players::noPlayer;

	}

};

#endif