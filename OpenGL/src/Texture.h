#pragma once
#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	int getWidth() const;
	int getHeight() const;

private:
	unsigned int m_RendererID;
	std::string m_FilePath;

	unsigned char* m_LocalBuffer;
	int m_Width;
	int m_Height;
	int m_BPP;
};

