#pragma once

#include <iostream>

using uchar = unsigned char;

class Colour
{
	public :

	Colour() = default;
	Colour(uchar r, uchar g, uchar b);

	friend Colour operator -(const Colour& one, const Colour& two);
	friend Colour operator +(const Colour& one, const Colour& two);
	friend Colour operator *(const Colour& one, const double&);

	friend std::ostream& operator << (std::ostream& of, const Colour& col);

	// litte endian order
	uchar m_B{0};
	uchar m_G{0}; 
	uchar m_R{0};

};