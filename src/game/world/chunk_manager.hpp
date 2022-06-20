#pragma once

#include "coordinate.hpp"
#include "chunk.hpp"

class ChunkManager {
public:
	// Adds a chunk to m_chunks at position and returns a reference to it
	Chunk& addChunk(const ChunkPosition position);

	// Locates chunk at position and returns reference if found, if not it returns an error chunk
	Chunk& getChunk(const ChunkPosition position);



	voxel_t getVoxel(const VoxelPosition& voxelPosition) const;

//private:
	ChunkPositionMap<Chunk> m_chunks;
};