#include "Renderer.h"

Renderer::Renderer(int width, int height) {
	glClearColor(0, 1, 1, 1);
	Shader shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");
	this->shader = shader;
	this->width = width;
	this->height = height;
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	shader.setMat4("projection", projection);
}

void Renderer::render(std::vector<Entity> entities, Camara camara) {
	shader.setFloat("material.shininess", entities[0].getModel().shininess);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entities[0].getModel().diffuseTexture);
	shader.setInt("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, entities[0].getModel().specularTexture);
	shader.setInt("material.specular", 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, entities[0].getModel().emissionTexture);
	shader.setInt("material.emission", 2);

	for (unsigned int i = 0; i < entities.size(); i++) {
		glm::mat4 view = camara.getViewMatrix(true);
		shader.setMat4("view", view);
		shader.setMat4("model", entities[i].modelMatrix);
		glBindVertexArray(entities[i].getModel().vertexArrayID);
		glDrawElements(GL_TRIANGLES, entities[i].getModel().indicesSize, GL_UNSIGNED_INT, NULL);
	}
}

void Renderer::lighting(DirectionalLight directionalLight, std::vector<PointLight> pointLights, std::vector<SpotLight> spotLights, Camara camara) {
	shader.setVec3("directionalLight.direction", directionalLight.direction);
	shader.setVec3("directionalLight.ambient", directionalLight.ambient);
	shader.setVec3("directionalLight.diffuse", directionalLight.diffuse);
	shader.setVec3("directionalLight.specular", directionalLight.specular);

	shader.setInt("numberOfLights.numberOfPointLights", pointLights.size());
	shader.setInt("numberOfLights.numberOfSpotLights", spotLights.size());

	for (unsigned int i = 0; i < pointLights.size(); i++) {
		char buffer[64];

		sprintf_s(buffer, "pointLight[%i].position", i);
		shader.setVec3(buffer, pointLights[i].position);

		sprintf_s(buffer, "pointLight[%i].ambient", i);
		shader.setVec3(buffer, pointLights[i].ambient);

		sprintf_s(buffer, "pointLight[%i].diffuse", i);
		shader.setVec3(buffer, pointLights[i].diffuse);

		sprintf_s(buffer, "pointLight[%i].specular", i);
		shader.setVec3(buffer, pointLights[i].specular);

		sprintf_s(buffer, "pointLight[%i].constantValue", i);
		shader.setFloat(buffer, pointLights[i].constantValue);

		sprintf_s(buffer, "pointLight[%i].linearValue", i);
		shader.setFloat(buffer, pointLights[i].linearValue);

		sprintf_s(buffer, "pointLight[%i].quadraticValue", i);
		shader.setFloat(buffer, pointLights[i].quadraticValue);
	}

	for (unsigned int i = 0; i < spotLights.size(); i++) {
		char buffer[64];

		sprintf_s(buffer, "spotLight[%i].position", i);
		shader.setVec3(buffer, spotLights[i].position);

		sprintf_s(buffer, "spotLight[%i].direction", i);
		shader.setVec3(buffer, spotLights[i].direction);

		sprintf_s(buffer, "spotLight[%i].cutOff", i);
		shader.setFloat(buffer, spotLights[i].cutOff);

		sprintf_s(buffer, "spotLight[%i].outerCutOff", i);
		shader.setFloat(buffer, spotLights[i].outerCutOff);

		sprintf_s(buffer, "spotLight[%i].ambient", i);
		shader.setVec3(buffer, spotLights[i].ambient);

		sprintf_s(buffer, "spotLight[%i].diffuse", i);
		shader.setVec3(buffer, spotLights[i].diffuse);

		sprintf_s(buffer, "spotLight[%i].specular", i);
		shader.setVec3(buffer, spotLights[i].specular);

		sprintf_s(buffer, "spotLight[%i].constantValue", i);
		shader.setFloat(buffer, spotLights[i].constantValue);

		sprintf_s(buffer, "spotLight[%i].linearValue", i);
		shader.setFloat(buffer, spotLights[i].linearValue);

		sprintf_s(buffer, "spotLight[%i].quadraticValue", i);
		shader.setFloat(buffer, spotLights[i].quadraticValue);
	}
}

void Renderer::clear() {
	glDeleteProgram(shader.getProgramID());
}


