#pragma once

// This is a class that stores a chunk mesh and functions for it

#include <array>
#include <vector>

#include <GLFW/glfw3.h>

#include "coordinate.hpp"



struct MeshFace {
	std::array<GLbyte, 12> vertices;
	GLbyte lightLevel;
};

class ChunkMesh {
public:
	// Constructor - Allocates vector space
	ChunkMesh(const ChunkPosition& chunkPosition) : position(chunkPosition) {}

	// Adds a face to the mesh
	void addFace(const MeshFace& face, const VoxelPosition& voxelPosition, GLuint texture);


	std::vector <float> vertices;
	std::vector <GLuint> indices;
	int indicesCount = 0;

	ChunkPosition position;
};


struct ChunkMeshCollection {
	ChunkMeshCollection(const ChunkPosition& chunkPosition);
	ChunkMesh voxelMesh;
	ChunkMesh floraMesh;
	ChunkMesh fluidMesh;
};