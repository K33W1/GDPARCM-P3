#include "Mesh.h"
#include <iostream>

Mesh::Mesh(const VertexArray* const va, const IndexBuffer* const ib)
	: va(va), ib(ib)
{
	
}

Mesh::~Mesh() {
	delete va;
	delete ib;
}

const VertexArray* const Mesh::getVertexArray() const
{
	return va;
}

const IndexBuffer* const Mesh::getIndexBuffer() const
{
	return ib;
}
