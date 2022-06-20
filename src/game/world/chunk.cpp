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
	voxels.fill( (position.y > 2) ? 0 : 1);
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