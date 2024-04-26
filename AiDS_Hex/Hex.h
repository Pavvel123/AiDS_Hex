#pragma once
enum Colour
{
	none,
	red,
	blue
};

class Hex
{
private:
	Colour colour;
	bool visited;

public:
	Hex(Colour colour);
	Colour GetColour() const;
	bool GetVisited() const;

	void SetVisited(bool vis);
};