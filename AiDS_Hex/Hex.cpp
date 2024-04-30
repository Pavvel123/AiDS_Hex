#include "Hex.h"

Hex::Hex() : colour(none), visited(false)
{
}

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

void Hex::SetColour(Colour col)
{
	colour = col;
}

void Hex::SetVisited(bool vis)
{
	visited = vis;
}

Hex::~Hex()
{
}
