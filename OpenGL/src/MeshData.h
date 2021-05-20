#pragma once
#include <string>
#include <vector>

class MeshData
{
public:
	MeshData(const std::string& filepath, const std::vector<float>& vertexData, const std::vector<unsigned int>& indices);

	const std::string& getFilePath() const;
	const std::vector<float>& getVertexData() const;
	const std::vector<unsigned int>& getIndices() const;

private:
	std::string filepath;
	std::vector<float> vertexData;
	std::vector<unsigned int> indices;
};
