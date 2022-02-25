#include "Math/Vector.h"

class ChessUtils
{
public:
	static int RoundToGrid(float x) { return round(abs(x)/100); }
};
