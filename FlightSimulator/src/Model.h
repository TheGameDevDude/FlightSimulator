#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "OBJLoader.h"
#include "Texture.h"
#include "VBOIndexer.h"

class Model {
public:
	int indicesSize;
	unsigned int vertexArrayID;
	float shininess;
	unsigned int diffuseTexture;
	unsigned int specularTexture;
	unsigned int emissionTexture;
private:
	unsigned int vertexBuffer;
	unsigned int uvBuffer;
	unsigned int normalBuffer;
	unsigned int ibo;
public:
	Model();
	Model(float shininess, char const* diffuse_path, char const* specular_path, char const* emmision_path, const char* obj_path);
	void clear();
};
