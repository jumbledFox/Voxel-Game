#include "voxel_data.hpp"

VoxelDataManager::VoxelDataManager() {
	VoxelData errorVoxel(
		"error", VoxelMeshStyle::Error, VoxelType::Error, 63
	);

	addVoxelData(errorVoxel);
}

void VoxelDataManager::addVoxelData(const VoxelData& voxel) {
	// Add the voxel to voxels
	voxels.push_back(voxel);

	// Set the ID of the voxel
	unsigned int lastElement = voxels.size() - 1;
	// I bet no one's reading this UwU
	voxels[lastElement].id = lastElement;

	// Add the voxel name and ID to nameIDs
	nameIDs.insert({ voxel.name, lastElement });
}

void VoxelDataManager::addVoxelsData(const std::vector<VoxelData>& voxels) {
	// For every voxel in the vector...
	for (const auto& v : voxels)
		// Add it!
		addVoxelData(v);
}


VoxelData VoxelDataManager::getVoxelData(const voxel_t& id) const {
	// If the ID is in range
	if (int(id) < int(voxels.size())) {
		// Return the voxel of ID
		return voxels[id];
	} else {
		// Oops!
		std::cerr << "Error! Tried to get voxel of unknown ID " << int(id) << "!\n";
		// Return the error voxel
		return voxels[0];
	}
}

VoxelData VoxelDataManager::getVoxelData(const std::string& name) const {
	// Return the voxel data
	return getVoxelData(getIdFromName(name));
}

voxel_t VoxelDataManager::getIdFromName(const std::string& name) const {
	// If the name is found in the names map
	if (nameIDs.find(name) != nameIDs.end()) {
		// Return the ID
		return nameIDs.at(name);
	}
	else {
		// Oops!
		std::cout << "Error! Tried to get voxel of unknown name '" << name << "'!\n";
		// Return the error voxel
		return 0;
	}
}