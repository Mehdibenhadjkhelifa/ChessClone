#include "Piece.h"
#include "Bishop.h"
extern Board ChessBoard;


	Bishop::Bishop(int PosX,int PosY,bool color) 
	{
		PiecePosX = PosX;
		PiecePosY = PosY;
		Color = color;

		int i(PiecePosX), j(PiecePosY);

		PieceInit();
		//Top Right Seach 
		while (i + 1 < FileLength && j + 1 < RankLength) 
		{
			if(ChessBoard.board[i+1][j+1].tileState== TileTaken || ChessBoard.board[i+1][j+1].tileState == TileTakenAndInPieceVision)
			{
				ChessBoard.board[i + 1][j + 1].tileState = TileTakenAndInPieceVision;
				break;
			
			}
			else
			{
				ChessBoard.board[i + 1][j + 1].tileState = TileInPieceVision;
				i++;
				j++;

			}


		}
		i = PiecePosX;
		j = PiecePosY;
		// Resetting i & j
		// Searching Top Left

		
		while (i + 1 < FileLength && j - 1 > -1)
		{
			if (ChessBoard.board[i + 1][j -1].tileState == TileTaken || ChessBoard.board[i + 1][j - 1].tileState == TileTakenAndInPieceVision)
			{
				ChessBoard.board[i + 1][j -1].tileState = TileTakenAndInPieceVision;
				break;

			}
			else
			{
				ChessBoard.board[i + 1][j -1].tileState = TileInPieceVision;
				i++;
				j--;

			}

		}

		i = PiecePosX;
		j = PiecePosY;
		//Resetting i & j
		// searching Bottom Right


		while (i -1 > -1 && j + 1 < RankLength)
		{
			if (ChessBoard.board[i - 1][j + 1].tileState == TileTaken || ChessBoard.board[i -1][j + 1].tileState == TileTakenAndInPieceVision)
			{
				ChessBoard.board[i - 1][j + 1].tileState = TileTakenAndInPieceVision;
				break;

			}
			else
			{
				ChessBoard.board[i - 1][j + 1].tileState = TileInPieceVision;
				i--;
				j++;

			}


		}

		i = PiecePosX;
		j = PiecePosY;
		//Resetting i & j
		//Searching Bottom Left

		while (i - 1 > -1 && j - 1 > -1)
		{
			if (ChessBoard.board[i - 1][j - 1].tileState == TileTaken || ChessBoard.board[i - 1][j - 1].tileState == TileTakenAndInPieceVision)
			{
				ChessBoard.board[i - 1][j - 1].tileState = TileTakenAndInPieceVision;
				break;

			}
			else
			{
				ChessBoard.board[i - 1][j - 1].tileState = TileInPieceVision;
				i--;
				j--;

			}

		}


	}


