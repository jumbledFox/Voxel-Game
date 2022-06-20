#include "keyboard.hpp"

#include "../window.hpp"

namespace {
	// Holds keys held down - true for every frame a key is held
	std::array<bool, GLFW_KEY_LAST> keysHeld;
	// Holds keys pressed - only true for frame pressed
	std::array<bool, GLFW_KEY_LAST> keysPressed;
}

void Keyboard::initialise() {
	// Set both arrays to false, just in case...
	resetHeld();
	resetPressed();
}


void Keyboard::updateKey(int key, int action) {
	if (action == 2) return; // If the action is GLFW_REPEAT, return
	keysHeld[key] = (action == 1) ? true : false; // For keys held, if the action is GLFW_PRESS, set the key to true, else false
	if (action == 1) keysPressed[key] = true; // If the action is GLFW_PRESS, set key to true, no need to set it false as it is reset elsewhere
}


bool Keyboard::keyHeld(int key) {
	return keysHeld[key]; // Returns specified key
}

bool Keyboard::keyPressed(int key) {
	return keysPressed[key]; // Returns specified key
}


void Keyboard::resetHeld() {
	// Make all elements false
	std::fill(keysHeld.begin(), keysHeld.end(), false);
}

void Keyboard::resetPressed() {
	// Make all elements false
	std::fill(keysPressed.begin(), keysPressed.end(), false);
}