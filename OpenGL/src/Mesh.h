#pragma once

class VertexArray;
class IndexBuffer;

class Mesh
{
public:
	Mesh(const VertexArray* const va, const IndexBuffer* const ib);

	const VertexArray* const getVertexArray() const;
	const IndexBuffer* const getIndexBuffer() const;

private:
	const VertexArray* const va;
	const IndexBuffer* const ib;
};

