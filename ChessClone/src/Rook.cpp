#include "ChessCore.h"
#include "Rook.h"
#include <iostream>

extern Board ChessBoard;




Rook::Rook(int PosX,int PosY,bool color)
	:Piece(PosX, PosY, color)
{
	CalculatePossibleMoves();
}

void Rook::CalculatePossibleMoves() 
{
	ClearPreviousPossibleMoves();
	int i(PiecePosX), j(PiecePosY);
	int RightOffset(j + 1), LeftOffset(j - 1), UpOffset(i + 1), DownOffset(i - 1);

	while (RightOffset < RankLength)
	{
		//check if tile has  this piece in it's pieces vision list
		auto It = std::find(ChessBoard.board[i][RightOffset].PiecesVisionList.begin(), ChessBoard.board[i][RightOffset].PiecesVisionList.end(), this);
		if (It != std::end(ChessBoard.board[i][RightOffset].PiecesVisionList))
		{
			if (ChessBoard.board[i][RightOffset].PieceInTile)
				break;
			else
			{
				RightOffset++;
				continue;
			}
		}



		ChessBoard.board[i][RightOffset].PiecesVisionList.emplace_back(this);
		if (ChessBoard.board[i][RightOffset].PieceInTile)
			break;
		
		RightOffset++;

	}


	while (LeftOffset > -1)
	{
		//check if tile has  this piece in it's pieces vision list
		auto It = std::find(ChessBoard.board[i][LeftOffset].PiecesVisionList.begin(), ChessBoard.board[i][LeftOffset].PiecesVisionList.end(), this);
		if (It != std::end(ChessBoard.board[i][LeftOffset].PiecesVisionList))
		{
			if (ChessBoard.board[i][LeftOffset].PieceInTile)
				break;
			else
			{
				LeftOffset--;
				continue;
			}
		}

		ChessBoard.board[i][LeftOffset].PiecesVisionList.emplace_back(this);
		if (ChessBoard.board[i][LeftOffset].PieceInTile)
			break;
		LeftOffset--;

	}

	while (UpOffset < FileLength)
	{
		//check if tile has  this piece in it's pieces vision list
		auto It = std::find(ChessBoard.board[UpOffset][j].PiecesVisionList.begin(), ChessBoard.board[UpOffset][j].PiecesVisionList.end(), this);
		if (It != std::end(ChessBoard.board[UpOffset][j].PiecesVisionList))
		{
			if (ChessBoard.board[UpOffset][j].PieceInTile)
				break;
			else
			{
				UpOffset++;
				continue;
			}
		}

		ChessBoard.board[UpOffset][j].PiecesVisionList.emplace_back(this);
		if (ChessBoard.board[UpOffset][j].PieceInTile)
			break;
		UpOffset++;

	}

	while (DownOffset > -1)
	{
		//check if tile has  this piece in it's pieces vision list
		auto It = std::find(ChessBoard.board[DownOffset][j].PiecesVisionList.begin(), ChessBoard.board[DownOffset][j].PiecesVisionList.end(), this);
		if (It != std::end(ChessBoard.board[DownOffset][j].PiecesVisionList))
		{
			if (ChessBoard.board[DownOffset][j].PieceInTile)
				break;
			else
			{
				DownOffset--;
				continue;
			}
		}

		ChessBoard.board[DownOffset][j].PiecesVisionList.emplace_back(this);
		if (ChessBoard.board[DownOffset][j].PieceInTile)
			break;
		DownOffset--;
	}

}





	
