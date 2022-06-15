
#include "fractalGenerator.h"
#include "colour.h"

#include <iostream>


int main()
{
	const int width = 800;
	const int height = 600;

	const double minRe = -2;
	const double maxRe = 1;
	const double minIm = -1.2;

	FractalGenerator fractalGen(
		width, 
		height, 
		minRe, 
		maxRe, 
		minIm
	);
	
	fractalGen.addZoom(Zoom{384, height -441, 0.5});
	fractalGen.addZoom(Zoom{397, height -322, 0.1});
	fractalGen.addZoom(Zoom{403, height -297, 0.5});

	fractalGen.addColourRange(0.0, Colour(0, 0, 255));
	fractalGen.addColourRange(0.01, Colour(0, 0, 150));
	fractalGen.addColourRange(0.05, Colour(10, 99, 71));
	fractalGen.addColourRange(0.08, Colour(40, 100, 60));
	fractalGen.addColourRange(0.10, Colour(50, 102, 40));
	fractalGen.addColourRange(0.20, Colour(155, 0, 115));
	fractalGen.addColourRange(0.50, Colour(155, 50, 155));
	fractalGen.addColourRange(1.0, Colour(255, 255, 255));

	fractalGen.run();

	fractalGen.write("test.bmp");
}