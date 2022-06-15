#ifndef Bitmap_h
#define Bitmap_h

#include <string>
#include <memory>
#include <vector>

#include "colour.h"

class Bitmap
{
	public :

	class InfoHeader;
	class FileHeader;

	Bitmap() = default;
	Bitmap(int width, int height);
	
	bool write (const std::string& name);

	void setPixel(int x, int y, const Colour& col);
	void setPixel(int x, int y, Colour&& col);

	private:
	int m_Width{0};
	int m_Height{0};
	std::unique_ptr<Colour[]> m_Data{nullptr};
};

#pragma pack(2)
class Bitmap::FileHeader
{
	public :
	char headerField[2] {'B', 'M'};
	int fileSize;
	int reserved{0};
	int offset;
};

#pragma pack(2)
class Bitmap::InfoHeader
{
	public:
	int headerSize{40};
	int width;
	int height;
	short int colourPlanes{1};
	short int bitsPerPixel{24};
	int compressionMethod{0};
	int imageSize{0};
	int horizontalRes{2400};
	int veticalRes{2400};
	int colourNumber{0};
	int importantColourNumber{0};
};

#endif