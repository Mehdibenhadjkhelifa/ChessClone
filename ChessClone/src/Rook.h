#pragma once

class Rook : public Piece 
{

protected:


public:
	Rook(int PosX, int PosY, bool color);
	virtual void CalculatePossibleMoves();
	Rook() = default;
	virtual std::string GetName() override{ return "Rook"; }
	
};
