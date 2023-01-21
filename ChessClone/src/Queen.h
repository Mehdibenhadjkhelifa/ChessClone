#pragma once
#include "Bishop.h"
#include "Rook.h"

class Queen :public Piece
{

protected:
	virtual void CalculatePossibleMoves();
	void CalculateLikeBishop();
	void CalculateLikeRook();
	//couldn't do it via inheritance
public:
	Queen(int PosX,int PosY,bool color);
	virtual std::string GetName()override { return "Queen"; };
};