#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Window {
	// This function sets up OpenGL with a window and all that
	void loadOpenGL(std::string windowTitle);
	// Cursor callback
	void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	// Keypress callback
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	// Process input
	void processInput();

	// Update - Checks for input, updates deltatime, etc
	void update();

	// Width and height of window
	const int WIDTH = 1000;
	const int HEIGHT = 900;

	// Window object
	extern GLFWwindow* window;

	// Bool showing whether the program is running
	extern bool running;

	// Get the delta time
	float getDeltatime();
};