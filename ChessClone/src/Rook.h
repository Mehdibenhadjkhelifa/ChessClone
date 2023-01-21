#pragma once

class Rook : public Piece 
{

protected:
	virtual void CalculatePossibleMoves();


public:
	Rook(int PosX, int PosY, bool color);

	virtual std::string GetName() override{ return "Rook"; }
	
};
