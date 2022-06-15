#pragma once 


class MandelBrot
{
	public :

	static int getIteration(double x, double y);
	
	static int getMaxIterations() {return m_maxIteration;}

	private :
	static const int m_maxIteration = 100;
};