#include "chunk_mesh_builder.hpp"

#include "voxel_data.hpp"

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

    
    //collection.voxelMesh.addFace(FRONT_FACE, { 0, 0, 0 }, 0);
    

    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {

                VoxelPosition voxelPosition(x, y, z);

                auto voxel = chunk.qGetVoxel(voxelPosition);

                auto voxData = voxelDataManager.getVoxelData(voxel);

                ChunkMesh* mesh;

                switch (voxData.type) {
                default:
                case VoxelType::Solid:
                case VoxelType::Error:
                    mesh = &collection.voxelMesh; break;
                case VoxelType::Liquid:
                    mesh = &collection.fluidMesh; break;
                case VoxelType::Flora:
                    mesh = &collection.floraMesh; break;
                case VoxelType::Gas:
                    mesh = &collection.voxelMesh; break;

                }

                // Lambda that makes checking and adding faces very easy
                static auto addFace = [&](VoxelPosition lookPos, MeshFace face, unsigned int texId = 0) {
                    if (voxelDataManager.getVoxelData(chunk.getVoxel(lookPos)).type != voxData.type)
                        mesh->addFace(face, voxelPosition, (texId == 0) ? voxData.topTexId : (texId == 1) ? voxData.sideTexId : voxData.bottomTexId);
                };
                
                // Every face
                static MeshFace faces[6] = { FRONT_FACE, BACK_FACE, RIGHT_FACE, LEFT_FACE, TOP_FACE, BOTTOM_FACE };

                switch (voxData.meshStyle) {
                case VoxelMeshStyle::Error:
                    // Add errors for every face
                    for (int i = 0; i < 6; i++)
                        mesh->addFace(faces[i], voxelPosition, 63);
                    break;

                case VoxelMeshStyle::Voxel:
                    //Check all sides of the voxel, and add faces if they can be seen
                    addFace({ x, y, z + 1 }, FRONT_FACE,  1);
                    addFace({ x, y, z - 1 }, BACK_FACE,   1);
                    addFace({ x + 1, y, z }, RIGHT_FACE,  1);
                    addFace({ x - 1, y, z }, LEFT_FACE,   1);
                    addFace({ x, y + 1, z }, TOP_FACE);
                    addFace({ x, y - 1, z }, BOTTOM_FACE, 2);
                    break;

                case VoxelMeshStyle::Cross:
                    mesh->addFace(CROSS_FACE_A, voxelPosition, voxData.sideTexId);
                    mesh->addFace(CROSS_FACE_B, voxelPosition, voxData.sideTexId);
                    break;

                default:
                    break;
                }
                
            }
        }
    }

    collection.voxelMesh.updateVertexArray();
    collection.floraMesh.updateVertexArray();
    collection.fluidMesh.updateVertexArray();

    return collection;
}