#pragma once
#include "Piece.h"


class Board {
private:


public:
	TileInfo board[ColumnLength][ColumnLength];
	Board();
	void BoardInit();

};