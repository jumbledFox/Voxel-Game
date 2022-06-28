#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"
#include "gl/texture.hpp"

#include "window.hpp"
#include "input/keyboard.hpp"

#include "game/world/chunk_manager.hpp"

#include "game/world/chunk_mesh_builder.hpp"

#include "game/voxel_data.hpp"

ChunkManager chunkManager;

VoxelDataManager voxelDataManager;

// TODO : Add destructors + tidy

int main() {
	Window::loadOpenGL("Window");

	gl::Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");

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

	voxelDataManager.addVoxelsData(defaultVoxelData);

	std::cout << voxelDataManager.getVoxelData(1).name << "\n";
	std::cout << voxelDataManager.getVoxelData(2).name << "\n";
	std::cout << voxelDataManager.getVoxelData(3).name << "\n";

	std::cout << (int)voxelDataManager.getIdFromName("tall_grass") << "\n";
	std::cout << (int)voxelDataManager.getVoxelData(3).id << "\n";

	auto e = voxelDataManager.getVoxelData(0);

	// Testing chunks
	std::cout << chunkManager.m_chunks.size() << "\n";
	std::cout << chunkManager.m_chunks.size() << "\n";
	std::cout << chunkManager.getChunk({0, 0, 0}).voxels[0] << "\n";

	std::vector<ChunkMesh> meshes;
	meshes.reserve(7 * 3 * 7);

	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 7; z++) {
				chunkManager.addChunk({ x, y, z });
			}
		}
	}
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 7; z++) {
				ChunkMesh voxelMesh = ChunkMeshBuilder::makeChunkMesh(chunkManager.getChunk({ x, y, z }), voxelDataManager).voxelMesh;

				voxelMesh.vertexArray = gl::VertexArray();
				voxelMesh.vertexArray.addVertexBuffer(voxelMesh.vertices, { {GL_FLOAT, 1, GL_FALSE} });
				voxelMesh.vertexArray.addIndexBuffer(voxelMesh.indices);


				meshes.push_back(voxelMesh);
			}
		}
	}


	gl::Texture texture("res/textureatlas.png", GL_RGBA);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);


	glm::mat4 proj = glm::perspective(glm::radians(35.0f), 1.f/.9f, 0.1f, 100.0f);

	glm::vec3 camPos = { 0, 0, 0 };

	float rot = 90;
	// Loop
	while (Window::running) {



		if (Keyboard::keyHeld(GLFW_KEY_W))
			camPos.x -= 1;
		if (Keyboard::keyHeld(GLFW_KEY_S))
			camPos.x += 1;
		if (Keyboard::keyHeld(GLFW_KEY_A))
			camPos.z += 1;
		if (Keyboard::keyHeld(GLFW_KEY_D))
			camPos.z -= 1;
		if (Keyboard::keyHeld(GLFW_KEY_SPACE))
			camPos.y -= 1;
		if (Keyboard::keyHeld(GLFW_KEY_LEFT_SHIFT))
			camPos.y += 1;


		if (Keyboard::keyHeld(GLFW_KEY_E))
			rot += 0.5f;
		if (Keyboard::keyHeld(GLFW_KEY_Q))
			rot -= 0.5f;

		std::cout << camPos.x << camPos.y << camPos.z << "\n";

		glm::mat4 vi{ 1.0f };
		vi = glm::rotate(vi, glm::radians(30.0f), { -1, 0, 0 });
		vi = glm::rotate(vi, glm::radians(rot), { 0, 1, 0 });
		vi = glm::translate(vi, camPos);
		glm::mat4 projview = proj * vi;


		// Update the window
		Window::update();

		glClearColor(26 / 255.0f, 28 / 255.0f, 44 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();


		glUniform3i(shader.getUniform("chunkPosition"), 0, 0, 0);
		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(projview));


		for (const auto& mesh : meshes) {
			glUniform3i(shader.getUniform("chunkPosition"), mesh.position.x, mesh.position.y, mesh.position.z);
			mesh.vertexArray.draw(GL_TRIANGLES);
		}
		

		// Swap buffers
		glfwSwapBuffers(Window::window);
		// Poll events
		glfwPollEvents();
	}

	// Exit
	glfwTerminate();
	return 0;
}