#include "Piece.h"
#include "ChessCore.h"
#include <iostream>
extern Board ChessBoard;
Piece::Piece()
	:PiecePosX(-1),PiecePosY(-1),Color(Black)
{
	


	//std::cout << "TEsting from piece" << std::endl;
}

//Piece::Piece(int PosX, int PosY, bool color) 
//{	
//	std::cout << "TEsting Here" << std::endl;
//
//}

void Piece::PieceInit()
{
	if (ChessBoard.board[PiecePosX][PiecePosY].tileState == TileInPieceVision)
		ChessBoard.board[PiecePosX][PiecePosY].tileState = TileTakenAndInPieceVision;
	else
		ChessBoard.board[PiecePosX][PiecePosY].tileState = TileTaken;



}

