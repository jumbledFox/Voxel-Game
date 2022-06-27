#include "chunk_mesh_builder.hpp"

#include "../voxel_data.hpp"

namespace {

    const MeshFace FRONT_FACE = { {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, 4 };
    const MeshFace LEFT_FACE = { {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 3 };
    const MeshFace BACK_FACE = { {0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, 4 };
    const MeshFace RIGHT_FACE = { {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, 3 };
    const MeshFace TOP_FACE = { {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}, 5 };
    const MeshFace BOTTOM_FACE = { {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1}, 2 };

    const MeshFace CROSS_FACE_A = { {1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1}, 3 };
    const MeshFace CROSS_FACE_B = { {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, 4 };
   
} // Empty namespace

ChunkMeshCollection ChunkMeshBuilder::makeChunkMesh(const Chunk& chunk, const VoxelDataManager& voxelDataManager) {

    ChunkMeshCollection collection(chunk.getPosition());

    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                VoxelPosition voxelPosition(x, y, z);

                auto voxel = chunk.qGetVoxel(voxelPosition);

                auto voxelData = voxelDataManager.getVoxelData(voxel);

                //collection.voxelMesh.addFace(FRONT_FACE,  voxelPosition, voxelData.sTextureId);
                //collection.voxelMesh.addFace(BACK_FACE,   voxelPosition, voxelData.sTextureId);
                //collection.voxelMesh.addFace(RIGHT_FACE,  voxelPosition, voxelData.sTextureId);
                collection.voxelMesh.addFace(LEFT_FACE,   voxelPosition, voxelData.sTextureId);
                //collection.voxelMesh.addFace(TOP_FACE,    voxelPosition, voxelData.tTextureId);
                //collection.voxelMesh.addFace(BOTTOM_FACE, voxelPosition, voxelData.bTextureId);
            }
        }
    }

    return collection;
}