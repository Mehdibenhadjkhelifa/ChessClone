#pragma once
#include "ChessCore.h"
#include "Board.h"


class Piece {
private:

protected:
	void PieceInit();
public:
	int PiecePosX;
	int PiecePosY;
	bool Color;

	/*virtual void Move() = 0;*/
	Piece();
	/*Piece(int PosX, int PosY, bool color);*/


};
