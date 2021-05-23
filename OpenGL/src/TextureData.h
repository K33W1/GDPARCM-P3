#pragma once
#include <string>
#include <vector>

class TextureData
{
public:
	TextureData(const std::string& filepath, const int width, const int height, const int BPP, unsigned char* buffer);

	const std::string& getFilePath() const;
	const int getWidth() const;
	const int getHeight() const;
	const int getBPP() const;
	unsigned char* getBuffer();

private:
	std::string filepath;
	int width;
	int height;
	int BPP;
	unsigned char* buffer;
};

