#include "chunk_manager.hpp"


Chunk& ChunkManager::addChunk(const ChunkPosition position) {
	auto itr = m_chunks.find(position);
	if (itr == m_chunks.cend()) {
		return m_chunks
			.emplace(std::piecewise_construct, std::forward_as_tuple(position),
				std::forward_as_tuple(*this, position))
			.first->second;
	}
	return itr->second;
}

Chunk& ChunkManager::getChunk(const ChunkPosition position) {
	auto itr = m_chunks.find(position);
	if (itr == m_chunks.cend()) {
		Chunk errorChunk(*this, { 0, 0, 0 });
		return errorChunk;
	}
	return itr->second;
}


voxel_t ChunkManager::getVoxel(const VoxelPosition& voxelPosition) const {
	auto chunkPosition = toChunkPosition(voxelPosition);
	auto itr = m_chunks.find(chunkPosition);
	if (itr == m_chunks.cend()) {
		return 0;
	}
	return itr->second.qGetVoxel(toLocalVoxelPosition(voxelPosition));
}