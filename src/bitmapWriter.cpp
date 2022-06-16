#include "bitmapWriter.h"

#include <fstream>
#include <iostream>

BitmapWriter::BitmapWriter(int width, int height)
: 
AbstracImageWriter(width, height), 
m_Data(new Colour[width*height])
{
}

bool BitmapWriter::write (const std::string& name) 
{
	FileHeader fileHeader;
	InfoHeader infoHeader;

	fileHeader.fileSize = sizeof(FileHeader) + 
		sizeof(InfoHeader) + 
		sizeof(Colour) * m_Height * m_Width;

	fileHeader.offset = sizeof(FileHeader) + sizeof(InfoHeader);

	infoHeader.width = m_Width;
	infoHeader.height = m_Height;

	std::ofstream of;

	of.open(name, std::ios::trunc|std::ios::binary|std::ios::out);

	if (!of.is_open())
		return false;

	of.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader)); 
	std::cout<<"ddd"<<std::endl;
	of.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader)); 
	std::cout<<"ddd"<<std::endl;
	of.write((char*)m_Data.get(), sizeof(Colour)*m_Width*m_Height); 
	std::cout<<"ddd"<<std::endl;
	
	of.close();


	return true;

}

void BitmapWriter::setPixel(int x, int y, const Colour& colour)
{
	m_Data[y*m_Width + x] = colour;
}


