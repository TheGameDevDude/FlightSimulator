#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Aircraft.h"
#include "Entity.h"
#include "Camara.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Shader.h"

class Renderer {
private:
	Shader shader;
	int width;
	int height;
public:
	Renderer(int width, int height);
	void render(std::vector<Entity> entities, Camara camara);
	void lighting(DirectionalLight directionalLight, std::vector<PointLight> pointLights, std::vector<SpotLight> spotLights, Camara camara);
	void clear();
};