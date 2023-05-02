#include "Tile.h"

Tile::Tile()
{
	setMine(false);
	setNumOfMines(0);
	setIsVisible(false);
	setIsFlagged(false);
}

Tile::Tile(bool m)
{
	setMine(m);
	setNumOfMines(0);
	setIsVisible(false);
	setIsFlagged(false);
}

void Tile::setMine(bool m)
{
	mine = m;
}

bool Tile::isMine() const
{
	return mine;
}

void Tile::setNumOfMines(int n)
{
	numOfMines = n;
}

int Tile::getNumOfMines() const
{
	return numOfMines;
}

void Tile::setIsVisible(bool v)
{
	isVisible = v;
}

bool Tile::getIsVisible() const
{
	return isVisible;
}

void Tile::setIsFlagged(bool f)
{
	isFlagged = f;
}

bool Tile::getIsFlagged() const
{
	return isFlagged;
}
