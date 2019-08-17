#include "Controls.h"

Controls::Controls(GLFWwindow* window) {
	this->window = window;
	forward = false;
	backward = false;
	leftArrow = false;
	rightArrow = false;
	upArrow = false;
	downArrow = false;
	flyUp = false;
	flyDown = false;
	mouseDX = 0.0f;
	mouseDY = 0.0f;
}

void Controls::tick() {
	mouse();
	keyboard();
}

void Controls::mouse() {
	//update window size
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	//get cursor position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	//calculate mouseDX and mouseDY
	mouseDX = mouseX - windowWidth / 2;
	mouseDY = -(mouseY - windowHeight / 2);
	//set back the cursor position
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

void Controls::keyboard() {
	//getting the keyboard inputs and setting up the values for booleans to control the camara
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		forward = true;
		backward = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		backward = true;
		forward = false;
	}
	else {
		forward = false;
		backward = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		leftArrow = true;
		rightArrow = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rightArrow = true;
		leftArrow = false;
	}
	else {
		leftArrow = false;
		rightArrow = false;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		upArrow = true;
		downArrow = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		upArrow = false;
		downArrow = true;
	}
	else {
		upArrow = false;
		downArrow = false;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		keyA = true;
		keyD = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		keyD = true;
		keyA = false;
	}
	else {
		keyD = false;
		keyA = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		flyUp = true;
		flyDown = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		flyDown = true;
		flyUp = false;
	}
	else {
		flyDown = false;
		flyUp = false;
	}
}