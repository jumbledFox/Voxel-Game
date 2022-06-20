#include <iostream>

#include "gl/shader.hpp"

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

	voxelDataManager.addVoxelData({ "grass",            0, 1, 2,   VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "stone",           3,          VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "stone_bricks",    4,          VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "crate",           5,          VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "explosive_crate", 6,          VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "oak_log",         9, 8, 9,    VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "oak_leaves",      10,         VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "oak_planks",      11,         VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "birch_log",       17, 16, 17, VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "birch_leaves",    18,         VoxelMeshStyle::Voxel, VoxelType::Solid });
	voxelDataManager.addVoxelData({ "birch_planks",    19,         VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "sand",            12, 12, 12, VoxelMeshStyle::Voxel, VoxelType::Solid });

	voxelDataManager.addVoxelData({ "tall_grass",      25,         VoxelMeshStyle::Cross, VoxelType::Flora });
	voxelDataManager.addVoxelData({ "dead_bush",       24,         VoxelMeshStyle::Cross, VoxelType::Flora });

	std::cout << voxelDataManager.getVoxelData(1).name << "\n";
	std::cout << voxelDataManager.getVoxelData(2).name << "\n";
	std::cout << voxelDataManager.getVoxelData(3).name << "\n";

	std::cout << (int)voxelDataManager.getIdFromName("tall_grass") << "\n";
	std::cout << (int)voxelDataManager.getVoxelData(3).id << "\n";


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


	// -- Testing OpenGL -- //
	unsigned int VertexBuffer;
	unsigned int VertexArray;

	// Generate Vertex Arrays and Buffers
	glGenBuffers(1, &VertexBuffer);
	glGenVertexArrays(1, &VertexArray);

	// Bind them
	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Get vertices into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Tell OpenGL what the vertices represent
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	// Lighting
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));

	// Enable vertexAttribPointer
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Element Buffer
	unsigned int ElementBuffer;
	glGenBuffers(1, &ElementBuffer);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);



	// Loop
	while (Window::running) {
		// Update the window
		Window::update();

		glClearColor(26 / 255.0f, 28 / 255.0f, 44 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();
		glBindVertexArray(VertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


		// Swap buffers
		glfwSwapBuffers(Window::window);
		// Poll events
		glfwPollEvents();
	}

	// Exit
	glfwTerminate();
	return 0;
}