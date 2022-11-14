# Tic Tac Toe

Tic Tac Toe is a simple project meant as a personal coding exercise for C++. While I've used the project as a means of learning the fundamentals of C++, I've also placed a heavy emphasis on effective, modern code design and best practices for the language. As such, I've experimented with the use of C++17 and C++20 features, such as string_views.

One emphasis for this project is the use of customizability and extendability. An example of this is the board itself: by default, the board is 3 x 3 tiles long like normal, but by modifying the maxRows and maxColumns const variables in tic-tac-toe.cpp, players can change the size of the board to any range they want, and the game's rules will scale perfectly with these changes.

## To-do

One major element I'd like to add is a rudimentary AI that the player can play against (currently, the game only supports a "hotseat" mode, in which two players take turns playing). In addition, in the program's theme of extendability, I plan on adding the support for more than two players, as well as allowing the user to adjust the size of the board at run-time.
