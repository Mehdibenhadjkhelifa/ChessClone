#pragma once

class King : public Piece 
{
protected:
	virtual void CalculatePossibleMoves()override;
public:
	King(int PosX, int PosY, bool color);
	virtual std::string GetName() { return "King"; }
};
