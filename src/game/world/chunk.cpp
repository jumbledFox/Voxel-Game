#include "chunk.hpp"
#include "chunk_manager.hpp"

namespace {
	bool voxelPositionOutOfBounds(const VoxelPosition& voxelPosition) {
		return
			voxelPosition.x < 0 || voxelPosition.x >= CHUNK_SIZE ||
			voxelPosition.y < 0 || voxelPosition.y >= CHUNK_SIZE ||
			voxelPosition.z < 0 || voxelPosition.z >= CHUNK_SIZE;
	}
}


Chunk::Chunk(ChunkManager& manager, const ChunkPosition position):
	mp_manager(manager),
	m_position(position)
{
	//voxels.fill( (position.y > 99) ? 1 : 2);
	voxels.fill(2);
	voxels[0] = 0;
	voxels[1] = 1;
	voxels[2] = 2;
	voxels[3] = 3;
	voxels[4] = 4;
	voxels[5] = 5;
	voxels[6] = 6;
	voxels[7] = 7;
	voxels[8] = 8;
	/*
	for (int x = 4; x < 10; x++) {
		for (int y = 4; y < 10; y++) {
			for (int z = 4; z < 10; z++) {
				voxels[toLocalVoxelIndex({ x, y, z })] = 1;
			}
		}
	}

	for (int x = 2; x < 14; x++) {
		for (int z = 3; z < 10; z++) {
			voxels[toLocalVoxelIndex({ x, 15, z })] = 1;
		}
	}*/
}



voxel_t Chunk::qGetVoxel(const VoxelPosition& voxelPosition) const {
	assert(!voxelPositionOutOfBounds(voxelPosition));
	return voxels[toLocalVoxelIndex(voxelPosition)];
}

void Chunk::qSetVoxel(const VoxelPosition& voxelPosition, voxel_t voxel) {
}

voxel_t Chunk::getVoxel(const VoxelPosition& voxelPosition) const {
	if (voxelPositionOutOfBounds(voxelPosition)) {
		return mp_manager.getVoxel(toGlobalVoxelPosition(voxelPosition, m_position));
	}

	return voxels[toLocalVoxelIndex(voxelPosition)];
}


void Chunk::setVoxel(const VoxelPosition& voxelPosition, voxel_t voxel) {

}



ChunkPosition Chunk::getPosition() const {
	return m_position;
}