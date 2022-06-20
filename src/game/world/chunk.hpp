#pragma once

#include <array>
#include <vector>

#include "coordinate.hpp"
#include "world_constants.hpp"

class ChunkManager;

using VoxelArray = std::array<voxel_t, CHUNK_VOLUME>;


class Chunk {
public:
	Chunk(ChunkManager& manager, const ChunkPosition position);

	// Gets a voxel, UNSAFE - if you try to get one thats out of bounds it errors
	voxel_t qGetVoxel(const VoxelPosition& voxelPosition) const;

	// Sets a voxel, UNSAFE - if you try to set one thats out of bounds it errors
	void qSetVoxel(const VoxelPosition& voxelPosition, voxel_t voxel);


	// Gets a voxel, if you try to get one thats out of bounds it'll return one from a neighbouring chunk
	voxel_t getVoxel(const VoxelPosition& voxelPosition) const;

	// Sets a voxel, if you try to set one thats out of bounds it'll change one in a neighbouring chunk
	void setVoxel(const VoxelPosition& voxelPosition, voxel_t voxel);


	// Gets the chunks position
	ChunkPosition getPosition() const;

	VoxelArray voxels{ 0 };
private:
	ChunkManager& mp_manager;
	ChunkPosition m_position;
};