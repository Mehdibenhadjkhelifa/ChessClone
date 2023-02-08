#pragma once
#include "Bishop.h"
#include "Rook.h"

class Queen :public Bishop , public Rook 
{

protected:
	virtual void CalculatePossibleMoves();
	//void CalculateLikeBishop();
	//void CalculateLikeRook();
public:
	Queen(int PosX,int PosY,bool color);
	virtual std::string GetName()override { return "Queen"; };
};