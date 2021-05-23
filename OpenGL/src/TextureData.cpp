#include "TextureData.h"

TextureData::TextureData(const std::string& filepath, const int width, const int height, const int BPP, unsigned char* buffer) :
	filepath(filepath), width(width), height(height), BPP(BPP), buffer(buffer)
{

}

const std::string& TextureData::getFilePath() const
{
	return filepath;
}

const int TextureData::getWidth() const
{
	return width;
}

const int TextureData::getHeight() const
{
	return height;
}

const int TextureData::getBPP() const
{
	return BPP;
}

unsigned char* TextureData::getBuffer()
{
	return buffer;
}