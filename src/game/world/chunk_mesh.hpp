#pragma once

// This is a class that stores a chunk mesh and functions for it

#include <array>
#include <vector>

#include <glad/glad.h>

#include "../../gl/vertex_array.hpp"

#include "coordinate.hpp"



struct MeshFace {
	std::array<GLbyte, 12> vertices;
	GLbyte lightLevel;
};

class ChunkMesh {
public:
	// Constructor - Allocates vector space
	ChunkMesh(const ChunkPosition& chunkPosition) : position(chunkPosition) {
		vertices.reserve(CHUNK_VOLUME * 2);
		indices.reserve(CHUNK_VOLUME * 2);
	}

	// Adds a face to the mesh
	void addFace(const MeshFace& face, const VoxelPosition& voxelPosition, GLuint texture);

	// Update the vertex array
	void updateVertexArray();

	std::vector <GLuint> vertices;
	std::vector <GLuint> indices;
	int indicesCount = 0;

	ChunkPosition position;

	gl::VertexArray vertexArray;
};


struct ChunkMeshCollection {
	ChunkMeshCollection(const ChunkPosition& chunkPosition);
	ChunkMesh voxelMesh;
	ChunkMesh floraMesh;
	ChunkMesh fluidMesh;
};