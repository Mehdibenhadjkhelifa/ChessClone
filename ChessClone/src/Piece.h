#pragma once

class Piece {
public:
	int PiecePosX;
	int PiecePosY;
	bool Color;
private:


protected:

	void PieceInit();
public:

	Piece();

	//virtual void Move() = 0;

	//Piece(int PosX, int PosY, bool color);


};
