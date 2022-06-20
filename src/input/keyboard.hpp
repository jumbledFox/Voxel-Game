#pragma once

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Keyboard {
	// Initialisation
	void initialise();

	// Update a key
	void updateKey(int key, int action);

	// Returns whether a key is held down
	bool keyHeld(int key);
	// Returns whether a key is pressed
	bool keyPressed(int key);

	// Resets all held keys
	void resetHeld();
	// Resets all pressed keys
	void resetPressed();
}