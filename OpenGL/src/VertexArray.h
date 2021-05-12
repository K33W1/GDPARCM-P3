#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void setBuffer(const VertexBuffer* const vb, const VertexBufferLayout* const layout);

	void bind() const;
	void unbind() const;

private:
	unsigned int m_RendererID;
};