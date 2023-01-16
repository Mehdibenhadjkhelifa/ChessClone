#pragma once
#include "ChessCore.h"

class Board {

	

public:
	TileInfo board[RankLength][FileLength];
	Board();
	void BoardInit();

};