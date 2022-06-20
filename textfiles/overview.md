# What I want this project to be
I want this project to be a voxel game with infinite world generation

# The World
## Chunks
The world will be split up into 16x16x16 cubic chunks. These chunks will be managed by a ChunkManager class
### The Chunk Class
The chunk class will contain an array of voxel_t (the type each voxel will be stored as, usually a uint8_t) that is ChunkSize^3 long. ChunkSize being 16 in this case. It will also have a reference to the ChunkManager and its position in the world
### The Chunk Manager Class
This class will hold an unordered map of ChunkPositions and chunks. This class will contain many methods relating to chunks, i.e. 
`Chunk& addChunk(ChunkPosition)` for adding a chunk to the map, locating it, then returning a reference to it.
`bool checkNeighbours(ChunkPosition)` for seeing if a chunk has all of its neighbors. This will return a bool if true.
`Chunk& getChunk(ChunkPosition)` This will locate a chunk and return it as a reference. If said chunk isnt found it'll return an errorChunk and print something to the console
`voxel_t getVoxel(VoxelPosition)` This will get the voxel at a specified world position
`ChunkPosition toChunkPosition(VoxelPosition)` This gets the position of a chunk from a world voxel position
`voxel_t setVoxel(VoxelPosition)` Sets the position of a voxel

### Coordinate
This is a file that will contain many functions related to coordinates and world positions, i.e.
`LocalVoxelPosition WorldToLocal()`

#### VoxelPosition
VoxelPosition is an alias for vector3(i32), It's used for world positions
#### LocalVoxelPosition
LocalVoxelPosition is an alias for vector3(uint16_t), used for positions inside chunks
#### ChunkPosition
This alias stores the position of a chunk in a vector3 of i32's


## Generation
The world will be generated with overlayed perlin noise. Biomes will also be generated with perlin noise, with different ranges of height being the thresholds. In each biome, different blocks / structures will be generated.

## Saving
TODO


# Rendering
## Chunks
### Building the mesh
To build a chunk mesh, I'll loop over every block and if any of its neighbors are transparent (i.e. air, glass, etc), a plane will be placed where they meet. This builds a sort of shell of the chunk
#### Looping through blocks
When you loop through the blocks sometimes you get one at the edge, and checking its neighbors results in funky numbers, so what I plan to do is have a function in the chunks which is called `GetBlockFromCoords(vec3 coords)`, It'll take in coordinates in form of a vec3 and calculate which block is at that position, if the index is out of range it'll use a reference to the ChunkManager to get the specified block in the chunk where that block is.