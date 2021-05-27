#pragma once
#include <string>

class TextureData
{
public:
	TextureData(const std::string& filepath, int width, int height, int BPP, unsigned char* buffer);

	const std::string& getFilePath() const;
	int getWidth() const;
	int getHeight() const;
	int getBPP() const;
	unsigned char* getBuffer() const;

private:
	std::string filepath;
	int width;
	int height;
	int BPP;
	unsigned char* buffer;
};

