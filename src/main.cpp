#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"
#include "gl/texture.hpp"
#include "gl/camera.hpp"

#include "window.hpp"
#include "input/keyboard.hpp"

#include "game/world/chunk_manager.hpp"
#include "game/world/chunk_mesh_builder.hpp"
#include "game/world/voxel_data.hpp"

#include "game/player.hpp"

ChunkManager chunkManager;

VoxelDataManager voxelDataManager;

// TODO : Add destructors + tidy

int main() {

	Window::loadOpenGL("jumbledFox's Super Duper Mega Ultra Voxel Breaker, Placer, and Manipulator V2 Deluxe");

	gl::Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	gl::Texture texture("res/textureatlas.png", GL_RGBA);

	std::vector<VoxelData> defaultVoxelData = {
		{ "air",             VoxelMeshStyle::None,  VoxelType::Gas,    63 },
		{ "grass",           VoxelMeshStyle::Voxel, VoxelType::Solid,  { 0, 1, 2 } },
		{ "dirt",            VoxelMeshStyle::Voxel, VoxelType::Solid,  { 2, 2, 2 } },
		{ "stone",           VoxelMeshStyle::Voxel, VoxelType::Solid,  3 },
		{ "stone_bricks",    VoxelMeshStyle::Voxel, VoxelType::Solid,  4 },
		{ "sand",            VoxelMeshStyle::Voxel, VoxelType::Solid,  12 },
		{ "sandstone",       VoxelMeshStyle::Voxel, VoxelType::Solid,  13 },
		{ "water",           VoxelMeshStyle::Voxel, VoxelType::Liquid, 7 },

		{ "crate",           VoxelMeshStyle::Voxel, VoxelType::Solid,  5 },
		{ "explosive_crate", VoxelMeshStyle::Voxel, VoxelType::Solid,  6 },

		{ "oak_log",         VoxelMeshStyle::Voxel, VoxelType::Solid,  { 9, 8, 9 } },
		{ "oak_leaves",      VoxelMeshStyle::Voxel, VoxelType::Solid,  10 },
		{ "oak_planks",      VoxelMeshStyle::Voxel, VoxelType::Solid,  11 },
		{ "birch_log",       VoxelMeshStyle::Voxel, VoxelType::Solid,  { 17, 16, 17 } },
		{ "birch_leaves",    VoxelMeshStyle::Voxel, VoxelType::Solid,  18 },
		{ "birch_planks",    VoxelMeshStyle::Voxel, VoxelType::Solid,  19 },

		{ "cactus",          VoxelMeshStyle::Voxel, VoxelType::Solid,  { 15, 14, 15 } },
		{ "tall_grass",      VoxelMeshStyle::Cross, VoxelType::Flora,  25 },
		{ "dead_bush",       VoxelMeshStyle::Cross, VoxelType::Flora,  24 },

		{ "blade",           VoxelMeshStyle::Voxel, VoxelType::Solid,  62 }
	};

	// Add voxels to the Voxel Data Manager
	voxelDataManager.addVoxelsData(defaultVoxelData);


	Camera camera(50.0f, 1.0f/0.9f);

	Player player;
	

	// Testing chunks

	Chunk& c = chunkManager.addChunk({ 0, 0, 0 });

	for (int x = 4; x < 12; x++) {
		for (int z = 4; z < 12; z++) {
			for (int y = 10; y < 16; y++) {
				c.qSetVoxel({ x, y, z }, voxelDataManager.getIdFromName("water"));
			}
		}
	}

	ChunkMeshCollection meshCollection = ChunkMeshBuilder::makeChunkMesh(chunkManager.getChunk({0, 0, 0}), voxelDataManager);


	shader.use();
	glUniform1ui(shader.getUniform("chunkSize"), CHUNK_SIZE);

	player.entity.position = { 0, 16, 0 };

	// Loop
	while (Window::running) {

		// Update the player and camera position
		player.update();
		camera.update(player.entity);

		if (Keyboard::keyPressed(GLFW_KEY_B)) {
			c.voxels.fill(voxelDataManager.getIdFromName("blade"));
			meshCollection = ChunkMeshBuilder::makeChunkMesh(chunkManager.getChunk({ 0, 0, 0 }), voxelDataManager);
		}

		// Update the window
		Window::update();

		// Clear the screen
		glClearColor(26 / 255.0f, 28 / 255.0f, 44 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		//std::cout << voxelDataManager.getVoxelData(chunkManager.getVoxel(coordinateToVoxel(player.entity.position - glm::vec3(0, 0.001f, 0)))).name << " - \n";
		//


		shader.use();

		// Set the projectionView matrix
		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getViewProjection()));

		glUniform3i(shader.getUniform("chunkPosition"), meshCollection.voxelMesh.position.x, meshCollection.voxelMesh.position.y, meshCollection.voxelMesh.position.z);

		meshCollection.voxelMesh.vertexArray.draw(GL_TRIANGLES);
		meshCollection.fluidMesh.vertexArray.draw(GL_TRIANGLES);
		glDisable(GL_CULL_FACE);
		meshCollection.floraMesh.vertexArray.draw(GL_TRIANGLES);
		glEnable(GL_CULL_FACE);

		

		// Swap buffers
		glfwSwapBuffers(Window::window);
		// Poll events
		glfwPollEvents();
	}

	// Exit
	glfwTerminate();
	return 0;
}