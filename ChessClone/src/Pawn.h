#pragma once

class Pawn:public Piece
{

protected:
	virtual void CalculatePossibleMoves()override;
public:
	Pawn(int PosX, int PosY, bool color);
	virtual std::string GetName()override { return "Pawn"; }
};