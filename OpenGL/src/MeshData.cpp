#include "MeshData.h"

MeshData::MeshData(const std::string& filepath, const std::vector<float>& vertexData, const std::vector<unsigned int>& indices)
	: filepath(filepath), vertexData(vertexData), indices(indices)
{
	
}

const std::string& MeshData::getFilePath() const
{
	return filepath;
}

const std::vector<float>& MeshData::getVertexData() const
{
	return vertexData;
}

const std::vector<unsigned>& MeshData::getIndices() const
{
	return indices;
}
