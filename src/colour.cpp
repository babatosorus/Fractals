#include "colour.h"

#include <algorithm>

Colour::Colour(uchar r, uchar g, uchar b)
  :
  m_R(r), m_G(g), m_B(b)
{
}

Colour operator - (const Colour& one, const Colour& two)
{
  Colour ret;

  if (two.m_R > one.m_R)
  {
    ret.m_R = 0;
  }
  else
  {
    ret.m_R = one.m_R - two.m_R;
  }

  if (two.m_G > one.m_G)
  {
    ret.m_G = 0;
  }
  else
  {
    ret.m_G = one.m_G - two.m_G;
  };

  if (two.m_B > one.m_B)
  {
    ret.m_B = 0;
  }
  else
  {
    ret.m_B = one.m_B - two.m_B;
  }

  return ret;
}

Colour operator + (const Colour& one, const Colour& two)
{
  Colour ret;

  if (one.m_R > (255 - two.m_R))
  {
    ret.m_R = 255;
  }
  else
  {
    ret.m_R = one.m_R + two.m_R;
  }

  if (one.m_G > (255 - two.m_G))
  {
    ret.m_G = 255;
  }
  else
  {
    ret.m_G = one.m_G + two.m_G;
  };

  if (one.m_B > (255 - two.m_B))
  {
    ret.m_B = 255;
  }
  else
  {
    ret.m_B = one.m_B + two.m_B;
  }

  return ret;

}

Colour operator * (const Colour& one, const double& factor)
{
  Colour ret;

  if (factor < 0)
  { 
    return ret;
  }

  double r = one.m_R * factor;
  if (r > 255)
  {
    ret.m_R = 255;
  }
  else
  {
    ret.m_R = r;
  }

  double g = one.m_G* factor;
  if (g > 255)
  {
    ret.m_G = 255;
  }
  else
  {
    ret.m_G = g;
  }

  double b = one.m_B* factor;
  if (b > 255)
  {
    ret.m_B = 255;
  }
  else
  {
    ret.m_B = b;
  }

  return ret;
}


std::ostream& operator << (std::ostream& of, const Colour& col)
{
  of<<"r :"<< (int)col.m_R <<" g: "<< (int)col.m_G <<" b: "<< (int)col.m_B;
  return of;
}

