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
	Window::loadOpenGL("Window");

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
		{ "dead_bush",       VoxelMeshStyle::Cross, VoxelType::Flora,  24 }
	};

	// Add voxels to the Voxel Data Manager
	voxelDataManager.addVoxelsData(defaultVoxelData);


	Camera camera(50.0f, 1.0f/0.9f);

	Player player;
	

	// Testing chunks

	chunkManager.addChunk({ 0, 0, 0 });
	//chunkManager.getChunk({ 0, 0, 0 }).voxels.fill(2);
	ChunkMeshCollection meshCollection = ChunkMeshBuilder::makeChunkMesh(chunkManager.getChunk({0, 0, 0}), voxelDataManager);




	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);

	shader.use();
	glUniform1ui(shader.getUniform("chunkSize"), CHUNK_SIZE);


	glm::vec3 camPos = { -22, 5, 3 };

	float rot = 90;
	// Loop
	while (Window::running) {



		if (Keyboard::keyHeld(GLFW_KEY_W))
			camPos -= player.front;
		if (Keyboard::keyHeld(GLFW_KEY_S))
			camPos += player.front;
		if (Keyboard::keyHeld(GLFW_KEY_A))
			camPos.z -= 1;
		if (Keyboard::keyHeld(GLFW_KEY_D))
			camPos.z += 1;
		if (Keyboard::keyHeld(GLFW_KEY_SPACE))
			camPos.y += 1;
		if (Keyboard::keyHeld(GLFW_KEY_LEFT_SHIFT))
			camPos.y -= 1;


		if (Keyboard::keyHeld(GLFW_KEY_E))
			rot += 0.5f;
		if (Keyboard::keyHeld(GLFW_KEY_Q))
			rot -= 0.5f;

		//std::cout << camPos.x << " " << camPos.y << " " << camPos.z << "\n";

		player.update();
		player.entity.position = { 40, -30, -15.5 };

		Entity cam;
		cam.rotation = player.entity.rotation;
		//cam.rotation = { 0, 90, 0 };
		cam.position = camPos;
		camera.update(cam);


		// Update the window
		Window::update();

		glClearColor(26 / 255.0f, 28 / 255.0f, 44 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();


		glUniform3i(shader.getUniform("chunkPosition"), 0, 0, 0);
		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getViewProjection()));


		glUniform3i(shader.getUniform("chunkPosition"), meshCollection.voxelMesh.position.x, meshCollection.voxelMesh.position.y, meshCollection.voxelMesh.position.z);
		meshCollection.voxelMesh.vertexArray.draw(GL_TRIANGLES);
		

		// Swap buffers
		glfwSwapBuffers(Window::window);
		// Poll events
		glfwPollEvents();
	}

	// Exit
	glfwTerminate();
	return 0;
}