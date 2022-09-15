#pragma once

#define black 0
#define white 1
enum TileState { TileNotTakenAndNotInPieceVision, TileNotTaken, TileTaken, TileNotInPieceVision, TileInPieceVision };
static const int ColumnLength = 8;
static const int RawLength = 8;
class Piece;

struct TileInfo
{
	int TileRaw;
	int TileColumn;
	Piece* PieceInTile;
	TileState tileState;

};

