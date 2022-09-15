#include "Board.h"

Board::Board() {

	for (int i = 0;i < RawLength;i++)
	{
		for (int j = 0;j < ColumnLength;j++) {

			board[i][j].TileRaw = i;
			board[i][j].TileColumn = j;
			board[i][j].PieceInTile = nullptr;
			board[i][j].tileState = TileNotTakenAndNotInPieceVision;

     	}
	}



}
void Board::BoardInit()
{



}
