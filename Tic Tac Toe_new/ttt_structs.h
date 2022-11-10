#ifndef TTT_STRUCTS
#define TTT_STRUCTS
#include <string_view>


constexpr int maxRows{ 5 };
constexpr int maxColumns{ 5 };

constexpr std::string_view alphabet{ "abcdefghijklmnopqrstuvwxyz" };

enum class Players
{
	noPlayer,
	player1,
	player2,
};

struct Square
{
	Players status{ Players::noPlayer };

};

struct Line
{
	Square s[maxRows]{};
};

struct Board
{
	Line l[maxColumns]{};
};

#endif