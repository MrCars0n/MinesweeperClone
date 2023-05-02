// Minesweeper
// Carson Kramer

#include <iostream>
#include "Board.h"
#include <string>
#include <stdlib.h>

using namespace std;

// Error check integers
void errorCheckInt(int&, int, int, bool, int);

// Error check characters
void errorCheckChar(char&, bool);

int main()
{
	Board b;
	int x, y;
	char turn;
	bool clear = false; // Temp variable for clearing cin stream

	while (!b.getMinesTripped() && !b.win())
	{
		cout << b;

		cout << "Choose to flag a tile as a mine (F), unflag a tile (U), or dig up a tile (D): ";
		errorCheckChar(turn, clear);

		cout << "Enter row selection (1 - " << b.getBoardSize() << "): ";
		errorCheckInt(x, 1, b.getBoardSize(), true, -1);

		cout << "Enter column selection (1 - " << b.getBoardSize() << "): ";
		errorCheckInt(y, 1, b.getBoardSize(), true, -1);

		if (turn == 'D')
		{
			b.selection(x - 1, y - 1);
		}
		else if (turn == 'U')
		{
			b.flag(x - 1, y - 1, false);
		}
		else
		{
			b.flag(x - 1, y - 1, true);
		}

		clear = true; // Only clear on first iteration

		system("CLS");
	}

	cout << b;

	if (b.getMinesTripped())
	{
		cout << "Mine tripped, you lost." << endl << endl;
	}
	
	if (b.win())
	{
		cout << "All mines have been marked, you win!" << endl << endl;
	}

	system("pause");
	return 0;
}

// Error check integers
void errorCheckInt(int& num, int lower, int upper, bool inclusive, int limitOperator)
{
	// Prompt
	cin >> num;
	if (inclusive) // Inclusive error check
	{
		if (lower != limitOperator && upper != limitOperator) // If lower and upper limit exist
		{
			while (cin.fail() || num < lower || num > upper)
			{
				cin.clear(); // clears the error from the input stream
				cin.ignore(10000000, '\n'); // remove anything remaining in the stream
				cout << "Invalid input. Value needs to be between " << lower << " and " << upper << " (inclusive). Please try again: ";
				cin >> num;
			}
		}
		else if (lower == limitOperator)  // If no lower limit
		{
			while (cin.fail() || num > upper)
			{
				cin.clear(); // clears the error from the input stream
				cin.ignore(10000000, '\n'); // remove anything remaining in the stream
				cout << "Invalid input. Value needs to be less than or equal to " << upper << ". Please try again: ";
				cin >> num;
			}
		}
		else if (upper == limitOperator) // If no upper limit
		{
			while (cin.fail() || num < lower)
			{
				cin.clear(); // clears the error from the input stream
				cin.ignore(10000000, '\n'); // remove anything remaining in the stream
				cout << "Invalid input. Value needs to be greater than or equal to " << lower << ". Please try again: ";
				cin >> num;
			}
		}
	}
	else // Exclusive error check
	{
		if (lower != limitOperator && upper != limitOperator) // If lower and upper limit exist
		{
			while (cin.fail() || num <= lower || num >= upper)
			{
				cin.clear(); // clears the error from the input stream
				cin.ignore(10000000, '\n'); // remove anything remaining in the stream
				cout << "Invalid input. Value needs to be between " << lower << " and " << upper << " (exclusive). Please try again: ";
				cin >> num;
			}
		}
		else if (lower == limitOperator)  // If no lower limit
		{
			while (cin.fail() || num >= upper)
			{
				cin.clear(); // clears the error from the input stream
				cin.ignore(10000000, '\n'); // remove anything remaining in the stream
				cout << "Invalid input. Value needs to be less than " << upper << ". Please try again: ";
				cin >> num;
			}
		}
		else if (upper == limitOperator) // If no upper limit
		{
			while (cin.fail() || num <= lower)
			{
				cin.clear(); // clears the error from the input stream
				cin.ignore(10000000, '\n'); // remove anything remaining in the stream
				cout << "Invalid input. Value needs to be greater than " << lower << ". Please try again: ";
				cin >> num;
			}
		}
	}
	cout << endl;
}

// Error check characters
void errorCheckChar(char& input, bool clear)
{
	if (clear)
	{
		cin.clear(); // clears the error from the input stream
		cin.ignore(10000000, '\n'); // remove anything remaining in the stream
	}

	// Prompt
	string str;
	getline(cin, str); // Get whole line
	input = toupper(str[0]); // Take first character of inputted string & capitalize

	// Error check
	while (cin.fail() || (input != 'F' && input != 'U' && input != 'D'))
	{
		cin.clear(); // clears the error from the input stream
		cin.ignore(10000000, '\n'); // remove anything remaining in the stream

		// Print error message
		cout << "Invalid input. Enter a 'F', 'U', or 'D': ";

		// Reprompt input
		getline(cin, str); // Get whole line
		input = toupper(str[0]); // Take first character of inputted string & capitalize
	}
}
