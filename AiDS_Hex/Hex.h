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

public:
	Hex(Colour colour);
};