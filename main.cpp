
#include "fractalBuilder.h"
#include "colour.h"

#include <iostream>


int main()
{
	static const int height = 600;
	static const int widht = 800;
	
	FractalBuilderParams params{
		widht, 
		height, 
		-2, 
		1, 
		-1.2
	};

	FractalBuilder fractalBuilder(params);
	
	fractalBuilder.addZoom({384, height - 441, 0.5})
			  	  .addZoom({397, height - 322, 0.1})
			  	  .addZoom({403, height - 297, 0.5});

	fractalBuilder.addColourRange(0.0, Colour(0, 0, 255))
			  	  .addColourRange(0.01, Colour(0, 0, 150))
	          	  .addColourRange(0.05, Colour(10, 99, 71))
			      .addColourRange(0.08, Colour(40, 100, 60))
			      .addColourRange(0.10, Colour(50, 102, 40))
			      .addColourRange(0.20, Colour(155, 0, 115))
			      .addColourRange(0.50, Colour(155, 50, 155))
			      .addColourRange(1.0, Colour(255, 255, 255));

	fractalBuilder.generate("test.bmp");

}