#include "fractalGenerator.h"
#include "mandelbrot.h"
#include "colour.h"

#include <limits>
#include <cmath>
#include <iostream>
#include <vector>

FractalGenerator::FractalGenerator(
	int width, 
	int height,
	double minReal,
	double maxReal,
	double minImaginary
)
: m_Viewport(width,height,minReal,maxReal,minImaginary)
{
}

void FractalGenerator::reset()
{
	m_Fractals = std::vector<int>(m_Viewport.getHeight() * m_Viewport.getWidth(), 0);
  	m_Histo = std::vector<int>(MandelBrot::getMaxIterations()+ 1, 0);
  	m_Bitmap= Bitmap(m_Viewport.getWidth(),m_Viewport.getHeight());

  	m_ColourLookUp.clear();
	m_RangeColStats = std::vector<int>(m_Colours.size());
}

void FractalGenerator::run()
{
	reset();
	computeIterations();
	computeColours();
}


void FractalGenerator::addColourRange(const double& range, const Colour& colour)
{
	m_Colours.push_back(std::make_pair(colour, range*MandelBrot::getMaxIterations()));
}

template <typename T>
void printHisto(const std::vector<T>& v)
{
	std::cout<<"coucou histo "<<v.size()<<std::endl;
	for (T vv : v)
		std::cout<<vv<<" ";

	std::cout<<std::endl;
}

void FractalGenerator::computeIterations()
{
	for (int y = 0; y < m_Viewport.getHeight(); ++y )
	{
		for (int x = 0; x < m_Viewport.getWidth(); ++x)
		{
			std::pair<double, double> complex = m_Viewport.screenCoordToComplex(x,y);
			int iterationNum = MandelBrot::getIteration(complex.first,complex.second);

			m_Histo[iterationNum]++;

			m_Fractals[y*m_Viewport.getWidth() + x] = iterationNum;
		}
	}

	//printHisto(m_Histo);
}

void FractalGenerator::computeColours()
{
	int colIdx = 0;
	m_RangeColStats[colIdx]+= m_Histo[0];
	m_ColourLookUp[0] = colIdx;
	for (int i = 1; i < m_Histo.size(); ++i)
	{
		if (i > m_Colours[colIdx+1].second && colIdx < (m_Colours.size() -1) )
		{
			++colIdx;
		}

		m_RangeColStats[colIdx]+= m_Histo[i];
		m_ColourLookUp[i] = colIdx;
	}

	std::cout<<"col stats"<<std::endl;
	for (auto it = m_RangeColStats.begin(); it != m_RangeColStats.end(); it++)
		std::cout<<*it<<" ";
	std::cout<<std::endl;

	std::cout<<"col lookup"<<std::endl;
	for (auto it = m_ColourLookUp.begin(); it != m_ColourLookUp.end(); it++)
		std::cout<<it->first<<":"<<it->second<<" ";
	std::cout<<std::endl;


	for (int y = 0; y < m_Viewport.getHeight(); ++y )
	{
		for (int x = 0; x < m_Viewport.getWidth(); ++x)
		{
			int iterationNum = m_Fractals[y*m_Viewport.getWidth() + x];
			Colour colour;
			if (iterationNum != MandelBrot::getMaxIterations())
			{
				//double col = pow(255,histo2[iterationNum]);
				//colour = startCol + (endCol - startCol)*histo2[iterationNum];
				int colId = m_ColourLookUp[iterationNum];
				//std::cout<<"iterationNum:"<<iterationNum<<" colId:"<<colId<<std::endl;
				// if (colId == m_Colours.size() -1 )
				// 	colour = m_Colours[m_Colours.size() -1].first;
				// else	
				{
					 Colour startCol = m_Colours[colId].first;
					 Colour endCol = m_Colours[colId+1].first;

					std::cout<<"start col="<< startCol<<" endCol="<< endCol;

					int pixels = 0;
					for (int i = m_Colours[colId].second; i <= iterationNum; i++)
						pixels += m_Histo[i];

					double ratio = ((double)pixels)/m_RangeColStats[colId];
					std::cout<<" ratio="<<ratio<<" iterationNum="<< iterationNum; 
					colour = startCol*(1-ratio) + endCol*ratio;
					std::cout<<" final col="<< colour<< std::endl;
				}

				//colour = getColour(histo2, iterationNum);
			}

			m_Bitmap.setPixel(x, y, colour);
		}
	}
}

/*
Colour FractalGenerator::getColour(const std::vector<int>& histo,  const double& num)
{
	Colour ret;

	if (m_Colours.size() <= 1)
	{
		double c = num*255;
		ret.m_R = c;
		return ret;
	}

	double num2 = num * (m_Colours.size() - 1);
	int idx =  std::floor(num2);

	
	if (idx == m_Colours.size() - 1)
	{	
		ret = m_Colours.back();
	}
	else
	{
		// int colorId = idx * ((double)(histo.size() - 1)/(m_Colours.size() - 1);
		// int nextColorId = (idx+1) * ((double)(histo.size() - 1)/(m_Colours.size() - 1);


		// const Colour& startCol = m_Colours[idx];
		// const Colour& endCol = m_Colours[idx+1];

		//ret = startCol*(1 - interp) + endCol*(interp);	
	}


	std::cout<<"num ==" << num <<" idx== "<<idx<<" col =="<< ret<<std::endl;

	return ret;
}
*/

int FractalGenerator::getHeight() const
{
	return m_Viewport.getHeight();
}

int FractalGenerator::getWidth() const
{
	return m_Viewport.getWidth();
}

void FractalGenerator::addZoom(const Zoom& zoom)
{
	m_Viewport.pushZoom(zoom);
}

void FractalGenerator::write(const std::string& filename)
{
	m_Bitmap.write(filename);
}




