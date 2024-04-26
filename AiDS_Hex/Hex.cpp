#include "Hex.h"

Hex::Hex(Colour colour) : colour(colour), visited(false)
{
}

Colour Hex::GetColour() const
{
	return colour;
}

bool Hex::GetVisited() const
{
	return visited;
}

void Hex::SetVisited(bool vis)
{
	visited = vis;
}
