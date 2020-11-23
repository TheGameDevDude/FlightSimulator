#pragma once

#include<GLFW/glfw3.h>

class Controls {
public:
	//for keyboard to control the camara
	bool forward;
	bool backward;
	bool rightArrow;
	bool leftArrow;
	bool upArrow;
	bool downArrow;
	bool flyUp;
	bool flyDown;
	bool keyA;
	bool keyD;
	//for mouse
	double mouseDX;
	double mouseDY;
	double mouseX;
	double mouseY;
	//display width and height
	int windowWidth;
	int windowHeight;
private:
	GLFWwindow* window;
public:
	Controls(GLFWwindow* window);
	void tick();
private:
	void mouse();
	void keyboard();
};