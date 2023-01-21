#pragma once

class Knight : public Piece
{
protected:
	virtual void CalculatePossibleMoves();
public:
	Knight(int PosX, int PosY, bool color);
	virtual std::string GetName()override { return "Knight"; }
};