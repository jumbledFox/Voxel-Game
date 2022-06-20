#include "coordinate.hpp"

int toLocalVoxelIndex(const VoxelPosition& position) {
	return (position.y * CHUNK_AREA) + (position.z * CHUNK_SIZE) + (position.x);
}


ChunkPosition toLocalVoxelPosition(const VoxelPosition& position) {
	return { (CHUNK_SIZE + (position.x % CHUNK_SIZE)) % CHUNK_SIZE,
			 (CHUNK_SIZE + (position.y % CHUNK_SIZE)) % CHUNK_SIZE,
			 (CHUNK_SIZE + (position.z % CHUNK_SIZE)) % CHUNK_SIZE };
}


ChunkPosition toChunkPosition(const VoxelPosition& position) {
	int x = position.x;
	int y = position.y;
	int z = position.z;

	return {
		x < 0 ? ((x - CHUNK_SIZE) / CHUNK_SIZE) : (x / CHUNK_SIZE),
		y < 0 ? ((y - CHUNK_SIZE) / CHUNK_SIZE) : (y / CHUNK_SIZE),
		z < 0 ? ((z - CHUNK_SIZE) / CHUNK_SIZE) : (z / CHUNK_SIZE)
	};
}



VoxelPosition toGlobalVoxelPosition(const VoxelPosition& localVoxelPosition,
	const ChunkPosition& chunkPosition) {
	return {
		chunkPosition.x * CHUNK_SIZE + localVoxelPosition.x,
		chunkPosition.y * CHUNK_SIZE + localVoxelPosition.y,
		chunkPosition.z * CHUNK_SIZE + localVoxelPosition.z
	};
}