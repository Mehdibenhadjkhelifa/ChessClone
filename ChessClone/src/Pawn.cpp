#include "ChessCore.h"
#include "Pawn.h"

extern Board ChessBoard;


Pawn::Pawn(int PosX,int PosY,bool color)
	:Piece(PosX, PosY, color)
{
	CalculatePossibleMoves();
}

void Pawn::CalculatePossibleMoves()
{
	ClearPreviousPossibleMoves();
	if (Color == White)
	{
		ChessBoard.board[PiecePosX + 1][PiecePosY + 1].PiecesVisionList.emplace_back(this);
		ChessBoard.board[PiecePosX - 1][PiecePosY + 1].PiecesVisionList.emplace_back(this);
	}
	else
	{
		ChessBoard.board[PiecePosX + 1][PiecePosY - 1].PiecesVisionList.emplace_back(this);
		ChessBoard.board[PiecePosX - 1][PiecePosY - 1].PiecesVisionList.emplace_back(this);
	}



}