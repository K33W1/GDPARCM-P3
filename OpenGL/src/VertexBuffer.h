#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned long long size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

private:
	unsigned int m_RendererID;
};

