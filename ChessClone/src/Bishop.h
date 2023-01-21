#pragma once

class Bishop :public Piece 
{
protected:
	virtual void CalculatePossibleMoves();

public:
	Bishop(int PosX, int PosY, bool color);

	virtual std::string GetName()override { return "Bishop"; }
	/*virtual void Move() override;*/
};

