#include "ChessCore.h"

Board::Board() {

	for (int i = 0;i < RankLength;i++)
	{
		for (int j = 0;j < FileLength;j++) {

			board[i][j].TileRaw = i;
			board[i][j].TileColumn = j;
			board[i][j].PieceInTile = nullptr;
			board[i][j].PiecesVisionList.reserve(6);

		}
	}



}
void Board::BoardInit()
{



}
