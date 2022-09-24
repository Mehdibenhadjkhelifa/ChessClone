#pragma once
/*#include "piece.h"
#include<vector>*/
#define Black 0
#define White 1
enum TileState { TileNotTakenAndNotInPieceVision, TileNotTaken, TileTaken, TileNotInPieceVision, TileInPieceVision , TileTakenAndInPieceVision};
const int FileLength = 8;
const int RankLength = 8;
class Piece;

struct TileInfo
{
	int TileRaw;
	int TileColumn;
	Piece* PieceInTile=nullptr;
	/*std::vector<Piece> PiecesVisionList;*/
	TileState tileState;

};

