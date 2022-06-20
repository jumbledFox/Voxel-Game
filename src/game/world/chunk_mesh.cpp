#include "chunk_mesh.hpp"

void ChunkMesh::addFace(const MeshFace& face, const VoxelPosition& voxelPosition, GLuint texture) {
	int index = 0;

	for (unsigned int i = 0; i < 4; i++) {
		GLubyte x = face.vertices[index++] + voxelPosition.x;
		GLubyte y = face.vertices[index++] + voxelPosition.y;
		GLubyte z = face.vertices[index++] + voxelPosition.z;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
		vertices.push_back(face.lightLevel);
		vertices.push_back(i);
		vertices.push_back(texture);
	}
	// First triangle
	indices.push_back(indicesCount);
	indices.push_back(indicesCount + 1);
	indices.push_back(indicesCount + 2);
	// Second triangle
	indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 3);
	indices.push_back(indicesCount);

	indicesCount += 4;
}


ChunkMeshCollection::ChunkMeshCollection(const ChunkPosition& chunkPosition)
	: voxelMesh(chunkPosition)
	, floraMesh(chunkPosition)
	, fluidMesh(chunkPosition) {}