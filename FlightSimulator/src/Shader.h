#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>

class Shader {
private:
	unsigned int programID;
public:
	Shader();
	Shader(const char* vertex_file_path, const char* fragment_file_path);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, glm::mat2& mat) const;
	void setMat3(const std::string& name, glm::mat3& mat) const;
	void setMat4(const std::string& name, glm::mat4& mat) const;
	unsigned int getProgramID() const;
	
private:
	static void compileShader(unsigned int shaderID, std::string shaderCode, const char *file_path);
	static unsigned int loadShaders(const char* vertex_file_path, const char* fragment_file_path);
	unsigned int getLocation(const std::string& name) const;
};

