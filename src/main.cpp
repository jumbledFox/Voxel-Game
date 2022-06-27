#include <iostream>

#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"

#include "window.hpp"
#include "input/keyboard.hpp"

#include "game/world/chunk_manager.hpp"

#include "game/world/chunk_mesh_builder.hpp"

#include "game/voxel_data.hpp"

ChunkManager chunkManager;

VoxelDataManager voxelDataManager;


int main() {
	Window::loadOpenGL("Window");

	gl::Shader shader("shaders/basic.vert", "shaders/basic.frag");

	voxelDataManager.addVoxelData({ "grass",           0, 1, 2,    VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "dirt",            2, 2, 2,    VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "stone",           3,          VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "stone_bricks",    4,          VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "water",           7, 7, 7,    VoxelMeshStyle::Voxel ,VoxelType::Liquid });

	voxelDataManager.addVoxelData({ "crate",           5,          VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "explosive_crate", 6,          VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "oak_log",         9, 8, 9,    VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "oak_leaves",      10,         VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "oak_planks",      11,         VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "birch_log",       17, 16, 17, VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "birch_leaves",    18,         VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "birch_planks",    19,         VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "sand",            12, 12, 12, VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "sandstone",       13, 13, 13, VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "cactus",          15, 14, 15, VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "tall_grass",      25,         VoxelMeshStyle::Cross, VoxelType::Flora });
	voxelDataManager.addVoxelData({ "dead_bush",       24,         VoxelMeshStyle::Cross, VoxelType::Flora });

	std::cout << voxelDataManager.getVoxelData(1).name << "\n";
	std::cout << voxelDataManager.getVoxelData(2).name << "\n";
	std::cout << voxelDataManager.getVoxelData(3).name << "\n";

	std::cout << (int)voxelDataManager.getIdFromName("tall_grass") << "\n";
	std::cout << (int)voxelDataManager.getVoxelData(3).id << "\n";

	auto e = voxelDataManager.getVoxelData(0);

	// Testing chunks
	std::cout << chunkManager.m_chunks.size() << "\n";
	chunkManager.addChunk({ 0, 0, 0 });
	std::cout << chunkManager.m_chunks.size() << "\n";
	std::cout << chunkManager.getChunk({0, 0, 0}).voxels[0] << "\n";


	std::vector<float> vertices = {
		// Pos               // Light
		-0.5f, -0.5f, 0.0f,  1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f,
		-0.4f,  0.5f, 0.0f,  1.0f,
		 0.4f,  0.5f, 0.0f,  0.0f,
		-1.0f, -1.0f, 0.0f,  0.6f,
		 1.0f,  1.0f, 0.0f,  0.2f
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		1, 2, 3,
		1, 2, 4,
		2, 3, 5
	};

	gl::VertexArray v;

	ChunkMeshCollection collection = ChunkMeshBuilder::makeChunkMesh(chunkManager.getChunk({ 0, 0, 0 }), voxelDataManager);

	v.create();
	v.addVertexBuffer(collection.voxelMesh.vertices, { {GL_FLOAT, 3, GL_FALSE}, {GL_FLOAT, 1, GL_FALSE} });
	v.addIndexBuffer(collection.voxelMesh.indices);

	// Loop
	while (Window::running) {

		// Update the window
		Window::update();

		glClearColor(26 / 255.0f, 28 / 255.0f, 44 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();

		v.draw(GL_TRIANGLES);

		// Swap buffers
		glfwSwapBuffers(Window::window);
		// Poll events
		glfwPollEvents();
	}

	// Exit
	glfwTerminate();
	return 0;
}