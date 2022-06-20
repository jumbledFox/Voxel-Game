#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <GLFW/glfw3.h>

#include "world/world_constants.hpp"

// Mesh style for voxels
enum class VoxelMeshStyle : uint8_t {
	Voxel = 0,
	Cross = 1,
	None = 2,

	Error
};

// Type of voxel
enum class VoxelType : uint8_t {
	Solid = 0,
	Flora = 1,
	Liquid = 2,
	Gas = 3,

	Error
};

// Stores Voxel Data
struct VoxelData {
	voxel_t id = 0;

	std::string name;

	GLuint tTextureId;
	GLuint sTextureId;
	GLuint bTextureId;

	VoxelMeshStyle meshStyle;
	VoxelType type;

	VoxelData(std::string name, GLuint TIDt, GLuint TIDs, GLuint TIDb, VoxelMeshStyle meshStyle, VoxelType type) :
		name(name),  tTextureId(TIDt), sTextureId(TIDs), bTextureId(TIDb), meshStyle(meshStyle), type(type) {
	}
	VoxelData(std::string name, GLuint TID, VoxelMeshStyle meshStyle, VoxelType type) :
		name(name), tTextureId(TID), sTextureId(TID), bTextureId(TID), meshStyle(meshStyle), type(type) {
	}
};

class VoxelDataManager {
public:
	VoxelDataManager();

	// Adds a voxel to the data manager
	void addVoxelData(const VoxelData& voxel);

	// Gets a voxel from its ID
	VoxelData getVoxelData(const voxel_t& id) const;
	// Gets a voxel from its name
	VoxelData getVoxelData(const std::string& name) const;

	// Get the ID of a voxel from its name
	voxel_t getIdFromName(const std::string& name) const;


	// Vector of VoxelDatas
	std::vector<VoxelData> voxels;
	// Map of names and their IDs
	std::unordered_map<std::string, voxel_t> nameIDs;
};