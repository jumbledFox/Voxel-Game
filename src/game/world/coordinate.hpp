#pragma once

#include <glm/glm.hpp>

#include "world_constants.hpp"

#include <unordered_map>


using ChunkPosition = glm::i32vec3;
using VoxelPosition = glm::i32vec3;

// So apparently for some reason I need a "Hash function" thing, I have no clue what this is so i just copied and pasted it, but one day I will...
// One day...
struct ChunkPositionHash {
    // http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf
    std::size_t operator()(const ChunkPosition& position) const
    {
        return (position.x * 88339) ^ (position.z * 91967) ^ (position.z * 126323);
    }
};

template <typename T>
using ChunkPositionMap = std::unordered_map<ChunkPosition, T, ChunkPositionHash>;



// Converts a local voxel position to an index of a voxel array
int toLocalVoxelIndex(const VoxelPosition& position);

// Converts a world voxel position to a local chunk voxel position
ChunkPosition toLocalVoxelPosition(const VoxelPosition& position);

// Converts a world voxel position to a chunk position
ChunkPosition toChunkPosition(const VoxelPosition& position);

// Converts a local voxel position and chunk to a world voxel position
VoxelPosition toGlobalVoxelPosition(const VoxelPosition& localVoxelPosition, const ChunkPosition& chunkPosition);

// Turns a regular vec3 coordinate into a block position
VoxelPosition coordinateToVoxel(const glm::vec3 coordinate);