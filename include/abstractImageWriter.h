#ifndef AbstracImageWriter_h
#define AbstracImageWriter_h

#include <string>

#include "colour.h"

class AbstracImageWriter
{
	public :

	AbstracImageWriter(int width = 0, int height = 0);
	
	virtual bool write (const std::string& name) = 0;
	virtual void setPixel(int x, int y, const Colour& col) = 0;

	protected :
	int m_Width{0};
	int m_Height{0};
};

#endif