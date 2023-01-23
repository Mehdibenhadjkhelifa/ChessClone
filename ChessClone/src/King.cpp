#include "ChessCore.h"
#include "King.h"

extern Board ChessBoard;

King::King(int PosX,int PosY,bool color)
	:Piece(PosX, PosY, color)
{

	CalculatePossibleMoves();

}

void King::CalculatePossibleMoves()
{
	ClearPreviousPossibleMoves();

	//this could be changed to check for squares that are safe before letting king to have vision on them.
	ChessBoard.board[PiecePosX+1][PiecePosY+1].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX-1][PiecePosY-1].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX+1][PiecePosY-1].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX-1][PiecePosY+1].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX][PiecePosY+1].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX][PiecePosY-1].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX+1][PiecePosY].PiecesVisionList.emplace_back(this);
	ChessBoard.board[PiecePosX-1][PiecePosY].PiecesVisionList.emplace_back(this);
}