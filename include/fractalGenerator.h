 #pragma once

#include "viewport.h"
#include "bitmap.h"

#include <string>
#include <vector>
#include <unordered_map>

class FractalGenerator
{
	public:
	FractalGenerator(
		int width, 
		int height,
		double minReal,
		double maxReal,
		double minImaginary
	);

	void run();
	void addZoom(const Zoom& zoom);
	void addColourRange(const double& range, const Colour & colour);
	void write(const std::string& filename);

	int getHeight() const;
	int getWidth() const;

	private:

	void computeIterations();
	void computeColours();
	//Colour getColour(const double& num);
	void reset();

	private:
	Viewport 							m_Viewport;
	Bitmap   							m_Bitmap;

	std::vector<int> 					m_Fractals;
	std::vector<int> 					m_Histo;

	std::unordered_map<int,int>			m_ColourLookUp;
	std::vector<std::pair<Colour,int>>	m_Colours; 
	std::vector<int>					m_RangeColStats;
};