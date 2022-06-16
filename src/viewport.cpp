#include "viewport.h"
#include <iostream>

Viewport::Viewport
(
  const int& width,
  const int& height,
  const double& minReal,
  const double& maxReal,
  const double& minImaginary
)
  : m_Width(width),
    m_Height(height),
    m_MinReal(minReal),
    m_MaxReal(maxReal),
    m_MinImaginary(minImaginary)
{
  double xScale = m_MaxReal - m_MinReal;
  double yScale = xScale*((double)height)/width;
  m_MaxImaginary = m_MinImaginary + yScale;
}

void Viewport::pushZoom(const Zoom& zoom)
{
  auto newCenter = screenCoordToComplex(zoom.m_XCenter, zoom.m_YCenter);

  double xScale = zoom.m_Scale*((m_MaxReal - m_MinReal)/2.0);
  double yScale = zoom.m_Scale*((m_MaxImaginary - m_MinImaginary)/2.0);

  m_MinReal = newCenter.first - xScale;
  m_MaxReal = newCenter.first + xScale;

  m_MinImaginary = newCenter.second - yScale;
  m_MaxImaginary = newCenter.second + yScale;

  std::cout<<"m_MinReal: "<< m_MinReal
           <<" m_MaxReal: "<< m_MaxReal
           <<" m_MinImaginary:" << m_MinImaginary
           <<"m_MaxImaginary: "<< m_MaxImaginary
           << std::endl;
}

std::pair<double,double> Viewport::screenCoordToComplex(const int&x,
    const int& y)
{
  double realFactor = (m_MaxReal - m_MinReal)/(m_Width -1);
  double imaginaryFactor = (m_MaxImaginary - m_MinImaginary)/(m_Height -1);

  return std::make_pair(
           m_MinReal + x*realFactor,
           m_MinImaginary + y*imaginaryFactor
         );
}

