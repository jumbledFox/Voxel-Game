#include "chunk_mesh.hpp"

#include <iostream>

void ChunkMesh::addFace(const MeshFace& face, const VoxelPosition& voxelPosition, GLuint texture) {
	int index = 0;

	for (unsigned int i = 0; i < 4; i++) {
		GLubyte x = face.vertices[index++] + voxelPosition.x;
		GLubyte y = face.vertices[index++] + voxelPosition.y;
		GLubyte z = face.vertices[index++] + voxelPosition.z;

		//std::cout << int(x) << " " << int(y) << " " << int(z) << "\n";
		// Assemble the vertex - Compress the coordinates, texture Coords, Light value, and texture into 4 bytes
		GLuint vertex =
			x | y << 5 | z << 10 | i << 15 | face.lightLevel << 17 | texture << 20;
		//std::cout << (int)x << " " << (int)y << " " << (int)z << " " << i << " " << (int)face.lightLevel << " " << 1 << "\n";
		vertices.push_back(vertex);
		//vertices.push_back(x);
		//vertices.push_back(y);
		//vertices.push_back(z);
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

void ChunkMesh::updateVertexArray() {
	vertexArray.destroy();
	vertexArray.create();
	
	vertexArray.addVertexBuffer(vertices, { { GL_FLOAT, 1, GL_FALSE } });
	vertexArray.addIndexBuffer(indices);
}

ChunkMeshCollection::ChunkMeshCollection(const ChunkPosition& chunkPosition)
	: voxelMesh(chunkPosition)
	, floraMesh(chunkPosition)
	, fluidMesh(chunkPosition) {}