#include "ChessCore.h"
#include "Queen.h"

extern Board ChessBoard;


Queen::Queen(int PosX, int PosY, bool color)
{
	

	PiecePosX = PosX;
	PiecePosY = PosY;
	Color = color;

	PieceInit();
	CalculatePossibleMoves();

}

void Queen::CalculatePossibleMoves()
{
	ClearPreviousPossibleMoves();
	CalculateLikeBishop();
	CalculateLikeRook();

}

void Queen::CalculateLikeBishop()
{
	int i(PiecePosX), j(PiecePosY);

	//Top Right Seach 
	while (i + 1 < FileLength && j + 1 < RankLength)
	{
		//check if tile has  this piece in it's pieces vision list
		auto It = std::find(ChessBoard.board[i + 1][j + 1].PiecesVisionList.begin(), ChessBoard.board[i + 1][j + 1].PiecesVisionList.end(), this);
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
void Queen::CalculateLikeRook()
{
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