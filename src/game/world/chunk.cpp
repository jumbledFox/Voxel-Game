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
	voxels[9] = 9;
	voxels[10] = 10;
	voxels[11] = 11;
	voxels[12] = 12;
	voxels[13] = 13;
	voxels[14] = 14;
	voxels[15] = 15;
	voxels[16] = 16;
	voxels[17] = 17;
	voxels[18] = 18;
	voxels[19] = 19;
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