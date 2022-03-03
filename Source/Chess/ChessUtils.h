#include "Piece.h"
#include "PieceMovementComponent.h"
#include "Math/Vector.h"

class ChessUtils
{
public:
	static int RoundToGrid(float x) { return round(abs(x)/100); }

	static UPieceMovementComponent* GetPieceMovementComponent(APiece* Piece){ return Piece->FindComponentByClass<UPieceMovementComponent>(); }
};
