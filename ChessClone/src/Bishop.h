#pragma once

class Bishop : virtual public Piece 
{
protected:

	virtual void CalculatePossibleMoves();
public:
	Bishop() = default;
	Bishop(int PosX, int PosY, bool color);
	virtual std::string GetName()override { return "Bishop"; }
	/*virtual void Move() override;*/
};

