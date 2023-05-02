#pragma once

class Tile
{
public:
	// Constructors
	Tile();
	Tile(bool);

	// Get and set
	void setMine(bool);
	bool isMine() const;

	void setNumOfMines(int);
	int getNumOfMines() const;

	void setIsVisible(bool);
	bool getIsVisible() const;

	void setIsFlagged(bool);
	bool getIsFlagged() const;

private:
	bool mine;
	int numOfMines;
	bool isVisible;
	bool isFlagged;
};