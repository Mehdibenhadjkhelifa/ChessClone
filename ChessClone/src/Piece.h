#pragma once

//thesee includes are for testing purposes only
#include <string>
#include <iostream>


class Piece {
public:
	int PiecePosX;
	int PiecePosY;
	bool Color;
private:


protected:

	void PieceInit();
	virtual void CalculatePossibleMoves();
	void ClearPreviousPossibleMoves();//this isn't optimised for each piece, maybe something for later
public:

	Piece();
	virtual std::string GetName() { return "nothing"; };
	//virtual void Move() = 0;

	//Piece(int PosX, int PosY, bool color);


};
