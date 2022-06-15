#pragma once

#include <list>
#include <utility>

class Zoom
{
	public :
	double m_XCenter{0};
	double m_YCenter{0};
	double m_Scale{1};
};


class Viewport
{
	public :

	Viewport
	(
		const int& width, 
		const int& height, 	
		const double& minReal,
		const double& maxReal,
		const double& minImaginary
	);
	
	void pushZoom(const Zoom& zoom);

	std::pair<double,double> screenCoordToComplex(const int&x, const int& y);

	int getWidth() const {return m_Width;}
	int getHeight() const {return m_Height;}

	private :

	int m_Width;
	int m_Height;

	double m_MinReal;
	double m_MaxReal;
	double m_MinImaginary;
	double m_MaxImaginary;
};