
#include "mandelbrot.h" 
#include <complex>

int MandelBrot::getIteration(double x, double y)
{
	std::complex<double> z = 0;
	std::complex<double> c(x, y);

	auto iterationNum = 0;
	while (iterationNum < m_maxIteration)
	{
		z = z*z + c;
		double r = std::abs(z);
		if (r  > 2.0)
			break;

		++iterationNum;
	}

	return iterationNum;
}
