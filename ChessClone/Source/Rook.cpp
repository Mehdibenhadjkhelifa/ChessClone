#include "Piece.h"

extern Board ChessBoard;



class Rook :public Piece 
{
public:
	Rook(int PosX,int PosY,bool color)
	{
		PiecePosX = PosX;
		PiecePosY = PosY;
		Color = color;
		int i(PiecePosX), j(PiecePosY);
		if (ChessBoard.board[i][j].tileState == TileInPieceVision)
			ChessBoard.board[i][j].tileState = TileTakenAndInPieceVision;
		else
			ChessBoard.board[i][j].tileState = TileTaken;
		int RightOffset(j+1), LeftOffset(j-1), UpOffset(i+1), DownOffset(i-1);


		while (RightOffset<RankLength)
		{
			if(ChessBoard.board[i][RightOffset].tileState == TileTaken || ChessBoard.board[i][RightOffset].tileState == TileTakenAndInPieceVision)
			{
				ChessBoard.board[i][RightOffset].tileState = TileTakenAndInPieceVision;
			/*	ChessBoard.board[i][RightOffset].PiecesVisionList.emplace_back(*this);*/
				break;
			}

			ChessBoard.board[i][RightOffset].tileState = TileInPieceVision;
	/*		ChessBoard.board[i][RightOffset].PiecesVisionList.emplace_back(*this);*/
			RightOffset++;

		}
		while (LeftOffset > -1)
		{
			if (ChessBoard.board[i][LeftOffset].tileState == TileTaken || ChessBoard.board[i][LeftOffset].tileState==TileTakenAndInPieceVision)
			{
				ChessBoard.board[i][LeftOffset].tileState = TileTakenAndInPieceVision;
			/*	ChessBoard.board[i][LeftOffset].PiecesVisionList.emplace_back(*this);*/
				break;
			}

			ChessBoard.board[i][LeftOffset].tileState = TileInPieceVision;
		/*	ChessBoard.board[i][LeftOffset].PiecesVisionList.emplace_back(*this);*/
			LeftOffset--;

		}

		while (UpOffset < FileLength)
		{
			if (ChessBoard.board[UpOffset][j].tileState == TileTaken || ChessBoard.board[UpOffset][j].tileState == TileTakenAndInPieceVision)
			{
				ChessBoard.board[UpOffset][j].tileState = TileTakenAndInPieceVision;
			/*	ChessBoard.board[UpOffset][j].PiecesVisionList.emplace_back(*this);*/
				break;
			}

			ChessBoard.board[UpOffset][j].tileState = TileInPieceVision;
		/*	ChessBoard.board[UpOffset][j].PiecesVisionList.emplace_back(*this);*/
			UpOffset++;

		}

		while (DownOffset >-1)
		{
			if (ChessBoard.board[DownOffset][j].tileState == TileTaken || ChessBoard.board[DownOffset][j].tileState==TileTakenAndInPieceVision)
			{
				ChessBoard.board[DownOffset][j].tileState = TileTakenAndInPieceVision;
			/*	ChessBoard.board[DownOffset][j].PiecesVisionList.emplace_back(*this);*/
				break;
			}

			ChessBoard.board[DownOffset][j].tileState = TileInPieceVision;
			/*ChessBoard.board[DownOffset][j].PiecesVisionList.emplace_back(*this);*/
			DownOffset--;

		}






			
	}




	



};