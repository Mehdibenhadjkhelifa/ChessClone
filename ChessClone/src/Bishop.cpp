#include "ChessCore.h"
#include "Bishop.h"
#include <iostream>
#include <algorithm>
extern Board ChessBoard;


	Bishop::Bishop(int PosX,int PosY,bool color) 
	{
		PiecePosX = PosX;
		PiecePosY = PosY;
		Color = color;

		PieceInit();
		CalculatePossibleMoves();
		
	}

	void Bishop::CalculatePossibleMoves()
	{
		ClearPreviousPossibleMoves();
		int i(PiecePosX), j(PiecePosY);

		//Top Right Seach 
		while (i + 1 < FileLength && j + 1 < RankLength)
		{
			//check if tile has  this piece in it's pieces vision list
			auto It = std::find(ChessBoard.board[i + 1][j + 1].PiecesVisionList.begin(), ChessBoard.board[i + 1][j + 1].PiecesVisionList.end(),this);
			if (It != std::end(ChessBoard.board[i + 1][j + 1].PiecesVisionList))
			{
				if (ChessBoard.board[i + 1][j + 1].PieceInTile)
					break;
				else
				{
					i++;
					j++;
					continue;
				}
			}


			ChessBoard.board[i + 1][j + 1].PiecesVisionList.emplace_back(this);
			if (ChessBoard.board[i + 1][j + 1].PieceInTile)
				break;
			
			i++;
			j++;

		}
		i = PiecePosX;
		j = PiecePosY;
		// Resetting i & j
		
		// Searching Top Left
		while (i + 1 < FileLength && j - 1 > -1)
		{
			//check if tile has  this piece in it's pieces vision list
			auto It = std::find(ChessBoard.board[i + 1][j - 1].PiecesVisionList.begin(), ChessBoard.board[i + 1][j - 1].PiecesVisionList.end(), this);
			if (It != std::end(ChessBoard.board[i + 1][j - 1].PiecesVisionList))
			{
				if (ChessBoard.board[i + 1][j - 1].PieceInTile)
					break;
				else
				{
					i++;
					j--;
					continue;
				}
			}

			ChessBoard.board[i + 1][j - 1].PiecesVisionList.emplace_back(this);

			if (ChessBoard.board[i + 1][j - 1].PieceInTile)
				break;

			i++;
			j--;

		}

		i = PiecePosX;
		j = PiecePosY;
		//Resetting i & j
		// searching Bottom Right


		while (i - 1 > -1 && j + 1 < RankLength)
		{
			//check if tile has  this piece in it's pieces vision list
			auto It = std::find(ChessBoard.board[i - 1][j + 1].PiecesVisionList.begin(), ChessBoard.board[i - 1][j + 1].PiecesVisionList.end(), this);
			if (It != std::end(ChessBoard.board[i - 1][j + 1].PiecesVisionList))
			{
				if (ChessBoard.board[i - 1][j + 1].PieceInTile)
					break;
				else
				{
					i--;
					j++;
					continue;
				}
			}


			ChessBoard.board[i - 1][j + 1].PiecesVisionList.emplace_back(this);

			if (ChessBoard.board[i - 1][j + 1].PieceInTile)
				break;
			i--;
			j++;

		}

		i = PiecePosX;
		j = PiecePosY;
		//Resetting i & j
		//Searching Bottom Left

		while (i - 1 > -1 && j - 1 > -1)
		{
			//check if tile has  this piece in it's pieces vision list
			auto It = std::find(ChessBoard.board[i - 1][j - 1].PiecesVisionList.begin(), ChessBoard.board[i - 1][j - 1].PiecesVisionList.end(), this);
			if (It != std::end(ChessBoard.board[i - 1][j - 1].PiecesVisionList))
			{
				if (ChessBoard.board[i - 1][j - 1].PieceInTile)
					break;
				else
				{
					i--;
					j--;
					continue;
				}
			}


			ChessBoard.board[i - 1][j - 1].PiecesVisionList.emplace_back(this);
			if (ChessBoard.board[i - 1][j - 1].PieceInTile)
				break;

			i--;
			j--;

		}

	}


