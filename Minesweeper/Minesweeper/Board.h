#pragma once

#include "Tile.h"
#include <fstream>

class Board
{
	// Overload the insertion operator to be able to print out a board object using <<
	friend std::ostream& operator<<(std::ostream&, const Board&);

public:
	// Constructors
	Board();

	// Get and set
	void setNumOfBoardMines(int);
	int getNumOfBoardMines() const;

	void setMinesTripped(bool);
	bool getMinesTripped() const;

	int getBoardSize() const;

	// Calculate the number of tiles on the board flagged
	int numOfFlaggedTiles() const;

	// Selection input
	void selection(int, int);

	// Flags / Un-Flags cell as mine
	void flag(int, int, bool);
	
	// Check if all the mines have been flagged
	bool win() const;
private:
	const static int BOARD_SIZE = 9;
	Tile grid[BOARD_SIZE][BOARD_SIZE];
	int numOfBoardMines;
	bool minesTripped;

	// Generate the mines randomly across the board
	void generateMines();

	// Check each square and assign it a number based on the number of mines that surround it
	void tileMineNums();

	// Shortened helper function for checking if a cell is visible and a zero value
	bool validZero(int, int);

	// If a tile is revealed with no bombs around it, make all the tiles around it visible
	bool zeroVisibility();
};