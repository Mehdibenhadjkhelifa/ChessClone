#pragma once

class Bishop :public Piece 
{
protected:

public:
	virtual void CalculatePossibleMoves();
	Bishop(int PosX, int PosY, bool color);
	Bishop() = default;
	virtual std::string GetName()override { return "Bishop"; }
	/*virtual void Move() override;*/
};

