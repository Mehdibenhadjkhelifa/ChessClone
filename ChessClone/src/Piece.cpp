#include "Piece.h"
#include "ChessCore.h"
#include <iostream>
extern Board ChessBoard;
#include "Bishop.h"
Piece::Piece()
	:PiecePosX(-1),PiecePosY(-1),Color(Black)
{

}
Piece::Piece(int PosX, int PosY, bool color) 
	:PiecePosX(PosX),PiecePosY(PosY),Color(color)
{	
	PieceInit();
}

void Piece::PieceInit()
{

	
	ChessBoard.board[PiecePosX][PiecePosY].PieceInTile = this;
	
	
	for (unsigned int i = 0;i < ChessBoard.board[PiecePosX][PiecePosY].PiecesVisionList.size();i += 1)
	{
		ChessBoard.board[PiecePosX][PiecePosY].PiecesVisionList[i]->CalculatePossibleMoves();

	}
}

void Piece::CalculatePossibleMoves()
{
	std::cout << "This shouldn't be called as a piece" << std::endl;
	return;
}

void Piece::ClearPreviousPossibleMoves()
{
	for (int i = 0;i < RankLength;i++)
	{
		for (int j = 0;j < FileLength;j++) 
		{
			auto It = std::find(ChessBoard.board[i][j].PiecesVisionList.begin(), ChessBoard.board[i][j].PiecesVisionList.end(), this);
			if (It != std::end(ChessBoard.board[i][j].PiecesVisionList))
				ChessBoard.board[i][j].PiecesVisionList.erase(It);


		}
	}
}

