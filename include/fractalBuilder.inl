
#include "mandelbrot.h"
#include "colour.h"

#include <limits>
#include <cmath>
#include <iostream>
#include <vector>

#include <type_traits>

template <typename T>
FractalBuilder<T>::FractalBuilder(
  const FractalBuilderParams& params
)
  : m_Viewport(
      params.width,
      params.height,
      params.minReal,
      params.maxReal,
      params.minImaginary
    )
{
  static_assert(
    std::is_base_of_v<AbstracImageWriter, T>,
    "the template argument is not of the expected type"
  );

}

template <typename T>
void FractalBuilder<T>::reset()
{
  m_Fractals = std::vector<int>(
                 m_Viewport.getHeight() * m_Viewport.getWidth(),
                 0
               );

  m_Histo = std::vector<int>(MandelBrot::getMaxIterations()+ 1, 0);
  m_Writer= BitmapWriter(m_Viewport.getWidth(),m_Viewport.getHeight());

  m_ColourLookUp.clear();
  m_RangeColStats = std::vector<int>(m_Colours.size());
}

template <typename T>
void FractalBuilder<T>::generate(const std::string& name)
{
  reset();
  computeIterations();
  computeColours();
  write(name);
}


template <typename T>
FractalBuilder<T>& FractalBuilder<T>::addColourRange(double range,
    const Colour& colour)
{
  m_Colours.emplace_back(colour,range*MandelBrot::getMaxIterations()));
  return *this;
}

// template <typename T>
// template <typename T>
// void printHisto(const std::vector<T>& v)
// {
// 	for (T vv : v)
// 		std::cout<<vv<<" ";

// 	std::cout<<std::endl;
// }

template <typename T>
void FractalBuilder<T>::computeIterations()
{
  for (int y = 0; y < m_Viewport.getHeight(); ++y )
  {
    for (int x = 0; x < m_Viewport.getWidth(); ++x)
    {
      std::pair  complex = m_Viewport.screenCoordToComplex(x,y);
      int iterationNum = MandelBrot::getIteration(complex.first,complex.second);

      m_Histo[iterationNum]++;

      m_Fractals[y*m_Viewport.getWidth() + x] = iterationNum;
    }
  }

  //printHisto(m_Histo);
}

template <typename T>
void FractalBuilder<T>::computeColours()
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

  /*
  std::cout<<"col stats"<<std::endl;
  for (auto it = m_RangeColStats.begin(); it != m_RangeColStats.end(); it++)
  	std::cout<<*it<<" ";
  std::cout<<std::endl;

  std::cout<<"col lookup"<<std::endl;
  for (auto it = m_ColourLookUp.begin(); it != m_ColourLookUp.end(); it++)
  	std::cout<<it->first<<":"<<it->second<<" ";
  std::cout<<std::endl;
  */

  for (int y = 0; y < m_Viewport.getHeight(); ++y )
  {
    for (int x = 0; x < m_Viewport.getWidth(); ++x)
    {
      int iterationNum = m_Fractals[y*m_Viewport.getWidth() + x];
      Colour colour;
      if (iterationNum != MandelBrot::getMaxIterations())
      {
        int colId = m_ColourLookUp[iterationNum];

        Colour startCol = m_Colours[colId].first;
        Colour endCol = m_Colours[colId+1].first;

        //std::cout<<"start col="<< startCol<<" endCol="<< endCol;

        int pixels = 0;
        for (int i = m_Colours[colId].second; i <= iterationNum; i++)
        {
          pixels += m_Histo[i];
        }

        double ratio = ((double)pixels)/m_RangeColStats[colId];
        //std::cout<<" ratio="<<ratio<<" iterationNum="<< iterationNum;
        colour = startCol*(1-ratio) + endCol*ratio;
        //std::cout<<" final col="<< colour<< std::endl;

        //colour = getColour(histo2, iterationNum);
      }

      m_Writer.setPixel(x, y, colour);
    }
  }
}

template <typename T>
void FractalBuilder<T>::write(const std::string& filename)
{
  m_Writer.write(filename);
}

template <typename T>
FractalBuilder<T>& FractalBuilder<T>::addZoom(const Zoom& zoom)
{
  m_Viewport.pushZoom(zoom);
  return *this;
}





