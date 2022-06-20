#pragma once

#include <stdint.h>

using voxel_t = uint8_t;

// Size of each chunk
const int CHUNK_SIZE = 16;
// Area of chunk
constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
// Volume of chunk
constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
