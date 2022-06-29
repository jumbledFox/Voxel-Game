#include "window.hpp"

#include "Input/Keyboard.hpp"
#include "gl/stb_image.h"

GLFWwindow* Window::window;
bool Window::running = true;
glm::vec2 Window::mousePosition;
bool Window::mouseMoving = false;

namespace {
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
}

void Window::loadOpenGL(std::string windowTitle) {
	// Initialise OpenGL with version 3.3 CORE
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Make a window
	Window::window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle.c_str(), NULL, NULL);

	// Check if the window generated alright
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window!\n";
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD!\n";
		exit(-1);
	}

	// Set cursor position callback
	glfwSetCursorPosCallback(window, cursorPosCallback);
	// Make cursor invisible and not leave window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set keypress callback
	glfwSetKeyCallback(window, keyCallback);

	// Set glfwSwapInterval
	glfwSwapInterval(1);

	stbi_set_flip_vertically_on_load(true);
	
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Depth
	glEnable(GL_DEPTH_TEST);


	// Reset keyboard
	Keyboard::initialise();
}

// Cursor Move Callback
void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	mousePosition = { xpos, ypos };
	mouseMoving = true;
}

// Key Callback
void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//std::cout << "Key: " << key << "  ScanCode: " << scancode << "  Action: " << action << "  Mods: " << mods << "\n";
	// Try to update the pressed key
	if(key != -1) Keyboard::updateKey(key, action);
}

// Handle keyboard
void Window::processInput() {

	// If the window should close or esc is pressed, close!
	if (glfwWindowShouldClose(Window::window) || Keyboard::keyPressed(GLFW_KEY_ESCAPE)) {
		Window::running = false;
	}

	// Example key press
	if (Keyboard::keyPressed(GLFW_KEY_T)) {
		std::cout << "T!\n";
	}

	// Example key hold
	if (Keyboard::keyHeld(GLFW_KEY_E)) {
		std::cout << "E!\n";
	}

	// Reset pressed
	Keyboard::resetPressed();
}


void Window::update() {
	// Process Input
	processInput();

	mouseMoving = false;

	// Set deltaTime
	float time = glfwGetTime();
	deltaTime = time - lastFrame;
	lastFrame = time;
}


// Get deltaTime
float Window::getDeltatime() {
	return deltaTime;
}