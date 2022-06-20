#pragma once

#include "chunk_mesh.hpp"
#include "chunk.hpp"
#include "../voxel_data.hpp"

namespace ChunkMeshBuilder {
    ChunkMeshCollection makeChunkMesh(const Chunk& chunk, const VoxelDataManager& voxelDataManager);
} // Builder namespace