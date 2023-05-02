#include "Board.h"
#include <random>
#include <iostream>

// Overload the insertion operator to be able to print out a board object using <<
std::ostream& operator<<(std::ostream& out, const Board& inputBoard)
{
	out << (char)1 << std::endl << "Number of mines: " << inputBoard.getNumOfBoardMines() << std::endl;
	out << "Number of tiles flagged: " << inputBoard.numOfFlaggedTiles() << std::endl;

	out << std::endl << "  ";
	for (int row = 0; row < inputBoard.BOARD_SIZE; row++)
	{
		out << " " << (row + 1) % 10 << " ";
	}
	out << std::endl;

	// Run through nested for loop of whole grid
	for (int row = 0; row < inputBoard.BOARD_SIZE; row++)
	{
		out << (row + 1) % 10 << " ";
		for (int col = 0; col < inputBoard.BOARD_SIZE; col++)
		{
			// Print flagged tiles first (if they have not already been dug up)
			if (inputBoard.grid[row][col].getIsFlagged() && !inputBoard.grid[row][col].getIsVisible())
			{
				out << " " << (char)16 << " "; // Flag is 16
			}
			// If the tile is visible, print the number of mines around it
			else if (inputBoard.grid[row][col].getIsVisible() || inputBoard.getMinesTripped())
			{
				if (inputBoard.grid[row][col].isMine())
				{
					out << " * ";
				}
				// If empty square, put dash
				else if (inputBoard.grid[row][col].getNumOfMines() == 0)
				{
					out << " - ";
				}
				// Print out number of mines that surround block
				else
				{
					out << " " << inputBoard.grid[row][col].getNumOfMines() << " ";
				}
			}
			else
			{
				out << " " << (char)240 << " ";
			}
		}
		out << std::endl;
	}
	out << std::endl;
	/*
	out << "  ";
	for (int row = 0; row < inputBoard.BOARD_SIZE; row++)
	{
		out << " " << row + 1 << " ";
	}
	out << std::endl;

	// Run through nested for loop of whole grid
	for (int row = 0; row < inputBoard.BOARD_SIZE; row++)
	{
		out << row + 1 << " ";
		for (int col = 0; col < inputBoard.BOARD_SIZE; col++)
		{
			if (inputBoard.grid[row][col].isMine())
			{
				out << " * "; // Flag is 16
			}
			// Print out number of mines that surround block
			else
			{
				out << " " << inputBoard.grid[row][col].getNumOfMines() << " ";
			}
		}
		out << std::endl;
	}
	*/

	return out;
}

// Constructors
Board::Board()
{
	// Set the number of mines on the board to the board size multiplied by 1.2
	setNumOfBoardMines(BOARD_SIZE * 1.2);
	generateMines();
	tileMineNums();
	setMinesTripped(false);
}

// Get and set
void Board::setNumOfBoardMines(int n)
{
	numOfBoardMines = n;
}
int Board::getNumOfBoardMines() const
{
	return numOfBoardMines;
}

void Board::setMinesTripped(bool m)
{
	minesTripped = m;
}
bool Board::getMinesTripped() const
{
	return minesTripped;
}

int Board::getBoardSize() const
{
	return BOARD_SIZE;
}

// Calculate the number of tiles on the board flagged
int Board::numOfFlaggedTiles() const
{
	int count = 0;

	// Run through nested for loop of whole grid
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (grid[row][col].getIsFlagged())
			{
				count++;
			}
		}
	}

	return count;
}

// Selection input
void Board::selection(int x, int y)
{
	// If valid input
	if (x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
	{
		if (grid[x][y].getIsFlagged())
		{
			grid[x][y].setIsFlagged(false);
		}
		if (grid[x][y].isMine())
		{
			setMinesTripped(true);
		}
		if (grid[x][y].getNumOfMines() == 0)
		{
			grid[x][y].setIsVisible(true);

			// Repeat the search for adjacent zero values until all are selected
			while (!zeroVisibility()) {}
		}
		else
		{
			grid[x][y].setIsVisible(true);
		}
	}
	else
	{
		std::cout << "Invalid selection" << std::endl;
	}
}

// Flags / Un-Flags cell as mine
void Board::flag(int row, int col, bool flag)
{
	// If not already visible
	if (!grid[row][col].getIsVisible())
	{
		grid[row][col].setIsFlagged(flag);
	}
}

// Check if all the mines have been flagged
bool Board::win() const
{
	int count = 0;

	// Run through nested for loop of whole grid
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			// If a mine is mis-Flagged
			if (grid[row][col].getIsFlagged() && !grid[row][col].isMine())
			{
				return false;
			}
			// If mine is flagged, add one to counter
			else if (grid[row][col].getIsFlagged() && grid[row][col].isMine())
			{
				count++;
			}
		}
	}

	// If the counted correctly flagged mines is equal to the number placed on the board
	return count == getNumOfBoardMines();
}

// If a tile is revealed with no bombs around it, make all the tiles around it visible
bool Board::zeroVisibility()
{
	// Temp bool value
	bool temp = true;

	// Run through nested for loop of whole grid
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (!grid[row][col].getIsVisible())
			{
				if (row == 0 && col == 0) // Top left tile
				{
					if (validZero(row, col + 1) || validZero(row + 1, col) || validZero(row + 1, col + 1))
					{
						grid[row][col].setIsVisible(true);
						temp = false;
					}
				}
				else if (row == BOARD_SIZE - 1 && col == 0) // Bottom left tile
				{
					if (validZero(row - 1, col) || validZero(row - 1, col + 1) || validZero(row, col + 1))
					{
						grid[row][col].setIsVisible(true);
						temp = false;
					}
				}
				else if (row == 0 && col == BOARD_SIZE - 1) // Top right tile
				{
					if (validZero(row, col - 1) || validZero(row + 1, col - 1) || validZero(row + 1, col))
					{
						grid[row][col].setIsVisible(true);
						temp = false;
					}
				}
				else if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) // Bottom right tile
				{
					if (validZero(row - 1, col - 1) || validZero(row - 1, col) || validZero(row, col - 1))
					{
						grid[row][col].setIsVisible(true);
						temp = false;
					}
				}
				else if (row > 0)
				{
					if (col > 0)
					{
						if (row < BOARD_SIZE - 1)
						{
							if (col < BOARD_SIZE - 1) // For all tiles not on a border
							{
								if (validZero(row - 1, col - 1) || validZero(row - 1, col) || validZero(row - 1, col + 1) || 
									validZero(row, col - 1) || validZero(row, col + 1) ||
									validZero(row + 1, col - 1) || validZero(row + 1, col) || validZero(row + 1, col + 1))
								{
									grid[row][col].setIsVisible(true);
									temp = false;
								}
							}
							else // For all tiles in the right-most column
							{
								if (validZero(row - 1, col - 1) || validZero(row - 1, col) || validZero(row, col - 1) ||
									validZero(row + 1, col - 1) || validZero(row + 1, col))
								{
									grid[row][col].setIsVisible(true);
									temp = false;
								}
							}
						}
						else // For all tiles in the bottom-most row
						{
							if (validZero(row - 1, col - 1) || validZero(row - 1, col) || validZero(row - 1, col + 1) ||
								validZero(row, col - 1) || validZero(row, col + 1))
							{
								grid[row][col].setIsVisible(true);
								temp = false;
							}
						}
					}
					else // For all tiles in the left-most column
					{
						if (validZero(row - 1, col) || validZero(row - 1, col + 1) ||
							validZero(row, col + 1) || validZero(row + 1, col) || validZero(row + 1, col + 1))
						{
							grid[row][col].setIsVisible(true);
							temp = false;
						}
					}
				}
				else // For all tiles in the first row
				{
					if (validZero(row, col - 1) || validZero(row, col + 1) ||
						validZero(row + 1, col - 1) || validZero(row + 1, col) || validZero(row + 1, col + 1))
					{
						grid[row][col].setIsVisible(true);
						temp = false;
					}
				}
			}
		}
	}

	return temp;
}

// Generate the mines randomly across the board
void Board::generateMines()
{
	std::random_device rdevice{};
	std::default_random_engine num{ rdevice() };
	std::uniform_int_distribution<unsigned int> randomNum{ 0, BOARD_SIZE - 1 };
	
	for (int i = 0; i < numOfBoardMines;)
	{
		// Randomly select coordinates
		int x = randomNum(num);
		int y = randomNum(num);

		// If a mine doesn't already exist at that location
		if (!grid[x][y].isMine())
		{
			grid[x][y].setMine(true);
			i++;
		}
	}
}

// Check each square and assign it a number based on the number of mines that surround it
void Board::tileMineNums()
{
	// Run through nested for loop of whole grid
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (row == 0 && col == 0) // Top left tile
			{
				grid[row][col].setNumOfMines(grid[row][col + 1].isMine() + grid[row + 1][col].isMine() + grid[row + 1][col + 1].isMine());
			}
			else if (row == BOARD_SIZE - 1 && col == 0) // Bottom left tile
			{
				grid[row][col].setNumOfMines(grid[row - 1][col].isMine() + grid[row - 1][col + 1].isMine() + grid[row][col + 1].isMine());
			}
			else if (row == 0 && col == BOARD_SIZE - 1) // Top right tile
			{
				grid[row][col].setNumOfMines(grid[row][col - 1].isMine() + grid[row + 1][col - 1].isMine() + grid[row + 1][col].isMine());
			}
			else if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) // Bottom right tile
			{
				grid[row][col].setNumOfMines(grid[row - 1][col - 1].isMine() + grid[row - 1][col].isMine() + grid[row][col - 1].isMine());
			}
			else if (row > 0)
			{
				if (col > 0)
				{
					if (row < BOARD_SIZE - 1)
					{
						if (col < BOARD_SIZE - 1) // For all tiles not on a border
						{
							grid[row][col].setNumOfMines(grid[row - 1][col - 1].isMine() + grid[row - 1][col].isMine() +
								grid[row - 1][col + 1].isMine() + grid[row][col - 1].isMine() + grid[row][col + 1].isMine() +
								grid[row + 1][col - 1].isMine() + grid[row + 1][col].isMine() + grid[row + 1][col + 1].isMine());
						}
						else // For all tiles in the right-most column
						{
							grid[row][col].setNumOfMines(grid[row - 1][col - 1].isMine() + grid[row - 1][col].isMine() +
								grid[row][col - 1].isMine() + grid[row + 1][col - 1].isMine() + grid[row + 1][col].isMine());
						}
					}
					else // For all tiles in the bottom-most row
					{
						grid[row][col].setNumOfMines(grid[row - 1][col - 1].isMine() + grid[row - 1][col].isMine() +
							grid[row - 1][col + 1].isMine() + grid[row][col - 1].isMine() + grid[row][col + 1].isMine());
					}
				}
				else // For all tiles in the left-most column
				{
					grid[row][col].setNumOfMines(grid[row - 1][col].isMine() +
						grid[row - 1][col + 1].isMine() + grid[row][col + 1].isMine() +
						grid[row + 1][col].isMine() + grid[row + 1][col + 1].isMine());
				}
			}
			else // For all tiles in the first row
			{
				grid[row][col].setNumOfMines(grid[row][col - 1].isMine() + grid[row][col + 1].isMine() +
					grid[row + 1][col - 1].isMine() + grid[row + 1][col].isMine() + grid[row + 1][col + 1].isMine());
			}
		}
	}
}

// Shortened helper function for checking if a cell is visible and a zero value
bool Board::validZero(int row, int col)
{
	return grid[row][col].getNumOfMines() == 0 && grid[row][col].getIsVisible();
}
