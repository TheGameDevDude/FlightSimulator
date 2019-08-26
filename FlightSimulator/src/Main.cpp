#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Aircraft.h"
#include "Camara.h"
#include "Controls.h"
#include "DirectionalLight.h"
#include "Entity.h"
#include "Model.h"
#include "PointLight.h"
#include "Renderer.h"
#include "SpotLight.h"

int main() {
	GLFWwindow* window;
	static int width = 1280;
	static int height = 720;

	if (!glfwInit()) {
		std::cout << "Error in initializing GLFW!" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(width, height, "OpenGL Portfolio", NULL, NULL);

	//Enabling openGL core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (!window) {
		std::cout << "Error in creating window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	std::cout << glGetString(GL_VERSION) << std::endl;

	if (glewInit() != GLEW_OK) {
		std::cout << "Error in initializing GLEW !" << std::endl;
		glfwTerminate();
		return -1;
	}

	Controls control(window);
	Camara camara(glm::vec3(0, 0, 0), 0, 0, 0);

	DirectionalLight directionalLight(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.5f, 0.1f), glm::vec3(1.0f, 0.5f, 0.1f));
	std::vector<PointLight> pointLights;
	pointLights.push_back(PointLight::PointLight(glm::vec3(0.5f, 4.0f, 0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.5f, 0.09f, 0.032f));
	std::vector<SpotLight> spotLights;
	spotLights.push_back(SpotLight::SpotLight(glm::vec3(), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 0.5f, 0.09f, 0.032f));
	
	Renderer renderer(width, height);

	Model runwayModel(32.0f, "res/textures/runway.png", "res/textures/blank.png", "res/textures/blank.png", "res/models/land.obj");
	std::vector<Entity> runway;
	runway.push_back(Entity::Entity(runwayModel, glm::vec3(0, 0, 0), glm::vec3(10, 1, 10), glm::vec3(0, 0, 0)));
	runway.push_back(Entity::Entity(runwayModel, glm::vec3(0, 0, -8), glm::vec3(10, 1, 10), glm::vec3(0, 0, 0)));

	Model landModel(32.0f, "res/textures/land.png", "res/textures/blank.png", "res/textures/blank.png", "res/models/land.obj");
	std::vector<Entity> lands;
	lands.push_back(Entity::Entity(landModel, glm::vec3(8, 0, 0), glm::vec3(10, 1, 10), glm::vec3(0, 0, 0)));
	lands.push_back(Entity::Entity(landModel, glm::vec3(-8, 0, 0), glm::vec3(10, 1, 10), glm::vec3(0, 90, 0)));
	lands.push_back(Entity::Entity(landModel, glm::vec3(0, 0, 8), glm::vec3(10, 1, 10), glm::vec3(0, 180, 0)));
	lands.push_back(Entity::Entity(landModel, glm::vec3(8, 0, -8), glm::vec3(10, 1, 10), glm::vec3(0, -180, 0)));
	lands.push_back(Entity::Entity(landModel, glm::vec3(-8, 0, -8), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
	lands.push_back(Entity::Entity(landModel, glm::vec3(-8, 0, 8), glm::vec3(10, 1, 10), glm::vec3(0, 90, 0)));
	lands.push_back(Entity::Entity(landModel, glm::vec3(8, 0, 8), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));

	for (int k = 16; k <= 60; k+=8) {
		lands.push_back(Entity::Entity(landModel, glm::vec3(0, 0, -k), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
		lands.push_back(Entity::Entity(landModel, glm::vec3(-8, 0, -k), glm::vec3(10, 1, 10), glm::vec3(0, 90, 0)));
		lands.push_back(Entity::Entity(landModel, glm::vec3(8, 0, -k), glm::vec3(10, 1, 10), glm::vec3(0, 0, 0)));
	}

	for (int d = 8; d >= -60; d -= 8) {
		for (int u = 16; u <= 60; u += 8) {
		lands.push_back(Entity::Entity(landModel, glm::vec3(u, 0, d), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
		}
	}

	for (int d = 8; d >= -60; d -= 8) {
		for (int u = 16; u <= 60; u += 8) {
			lands.push_back(Entity::Entity(landModel, glm::vec3(-u, 0, d), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
		}
	}


	for (int k = 16; k <= 60; k += 8) {
		lands.push_back(Entity::Entity(landModel, glm::vec3(0, 0, k), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
		lands.push_back(Entity::Entity(landModel, glm::vec3(-8, 0, k), glm::vec3(10, 1, 10), glm::vec3(0, 90, 0)));
		lands.push_back(Entity::Entity(landModel, glm::vec3(8, 0, k), glm::vec3(10, 1, 10), glm::vec3(0, 0, 0)));
	}

	for (int d = 8; d >= -60; d -= 8) {
		for (int u = 16; u <= 60; u += 8) {
			lands.push_back(Entity::Entity(landModel, glm::vec3(u, 0, -d), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
		}
	}

	for (int d = 8; d >= -60; d -= 8) {
		for (int u = 16; u <= 60; u += 8) {
			lands.push_back(Entity::Entity(landModel, glm::vec3(-u, 0, -d), glm::vec3(10, 1, 10), glm::vec3(0, -90, 0)));
		}
	}


	Aircraft aircraft(glm::vec3(0, 10, 35));

	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - prevTime);
		prevTime = currentTime;

		//camara.move(control, deltaTime);
		aircraft.tick(control, camara, deltaTime);

		spotLights[0].position = camara.position;
		spotLights[0].direction = camara.direction;
		renderer.lighting(directionalLight, pointLights, spotLights, camara);
		renderer.render(runway, camara);
		renderer.render(lands, camara);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//deleting 
	runwayModel.clear();
	renderer.clear();

	glfwTerminate();
	return 0;
}