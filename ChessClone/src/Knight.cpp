#include "ChessCore.h"
#include "Knight.h"

extern Board ChessBoard;

Knight::Knight(int PosX, int PosY, bool color)
	:Piece(PosX, PosY, color)
{
	CalculatePossibleMoves();
}

void Knight::CalculatePossibleMoves()
{
	ClearPreviousPossibleMoves();
	int i(PiecePosX), j(PiecePosY);

	if(i+2<RankLength && j+1 < FileLength)
		ChessBoard.board[i + 2][j + 1].PiecesVisionList.emplace_back(this);

	if (i + 2 < RankLength && j - 1 > -1)
		ChessBoard.board[i + 2][j - 1].PiecesVisionList.emplace_back(this);

	if (i - 2 > -1 && j + 1 < FileLength)
		ChessBoard.board[i - 2][j + 1].PiecesVisionList.emplace_back(this);

	if (i - 2 > -1 && j - 1 > -1)
		ChessBoard.board[i - 2][j - 1].PiecesVisionList.emplace_back(this);

	if (i + 1 < RankLength && j + 2 < FileLength)
		ChessBoard.board[i + 1][j + 2].PiecesVisionList.emplace_back(this);

	if (i + 1 < RankLength && j - 2 > -1)
		ChessBoard.board[i + 1][j - 2].PiecesVisionList.emplace_back(this);

	if (i - 1 > -1 && j + 2 < FileLength)
		ChessBoard.board[i - 1][j + 2].PiecesVisionList.emplace_back(this);

	if (i - 1 > -1 && j - 2 > -1)
		ChessBoard.board[i - 1][j - 2].PiecesVisionList.emplace_back(this);



}