#ifndef Bitmap_h
#define Bitmap_h

#include <string>
#include <memory>
#include <vector>

#include "abstractImageWriter.h"

class BitmapWriter : public AbstracImageWriter
{
	public :

	class InfoHeader;
	class FileHeader;

	BitmapWriter(int width = 0 , int height = 0);
	
	bool write(const std::string& name) override;
	void setPixel(int x, int y, const Colour& col) override;

	private:
	std::unique_ptr<Colour[]> m_Data{nullptr};
};

#pragma pack(2)
class BitmapWriter::FileHeader
{
	public :
	char headerField[2] {'B', 'M'};
	int fileSize;
	int reserved{0};
	int offset;
};

#pragma pack(2)
class BitmapWriter::InfoHeader
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