#pragma once

#include "viewport.h"
#include "bitmapWriter.h"

#include <string>
#include <vector>
#include <unordered_map>

struct FractalBuilderParams
{
  int width;
  int height;
  double minReal;
  double maxReal;
  double minImaginary;
};

template <typename T>
class FractalBuilder
{
public:

  FractalBuilder(
    const FractalBuilderParams& params
  );

  FractalBuilder& addZoom(const Zoom& zoom);

  FractalBuilder& addColourRange(
    double range,
    const Colour & colour
  );

  void generate(const std::string& filename);

private:

  void reset();
  void computeIterations();
  void computeColours();
  void write(const std::string& filename);

private:
  Viewport 								            m_Viewport;
  T   									              m_Writer;

  std::vector<int> 						        m_Fractals;
  std::vector<int> 						        m_Histo;

  std::unordered_map<int,int>			    m_ColourLookUp;
  std::vector<std::pair<Colour,int>>	m_Colours;
  std::vector<int>						        m_RangeColStats;
};

#include "fractalBuilder.inl"