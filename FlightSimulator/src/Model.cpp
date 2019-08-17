#include "Model.h"

Model::Model() {

}

Model::Model(float shininess, char const * diffuse_path, char const * specular_path, char const * emmision_path, char const * obj_path) {
	this->shininess = shininess;
	diffuseTexture = Texture::loadTexture(diffuse_path);
	specularTexture = Texture::loadTexture(specular_path);
	emissionTexture = Texture::loadTexture(emmision_path);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	char buffer[800];
	sprintf_s(buffer, obj_path);

	bool res = OBJLoader::loadOBJ(buffer, vertices, uvs, normals);



	std::vector<unsigned int> indices;
	std::vector<glm::vec3> ind_vertices;
	std::vector<glm::vec2> ind_uvs;
	std::vector<glm::vec3> ind_normals;

	VBOIndexer::indexVBO(vertices, uvs, normals, indices, ind_vertices, ind_uvs, ind_normals);

	indicesSize = indices.size();

	//vao
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//vbo for position
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, ind_vertices.size() * sizeof(glm::vec3), &ind_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	//vbo for texture coordinates
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, ind_uvs.size() * sizeof(glm::vec3), &ind_uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	//vbo for normals coordinates
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, ind_normals.size() * sizeof(glm::vec3), &ind_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	//for index buffer
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	vertices.end();
	uvs.end();
	normals.end();
	indices.end();
	ind_vertices.end();
	ind_uvs.end();
	ind_normals.end();
}

void Model::clear() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vertexArrayID);
}
