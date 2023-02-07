#pragma once

class Rook :virtual public Piece 
{
	
protected:

	virtual void CalculatePossibleMoves();

public:
	Rook() = default;
	Rook(int PosX, int PosY, bool color);
	virtual std::string GetName() override{ return "Rook"; }
	
};
