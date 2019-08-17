#include "Shader.h"

Shader::Shader() {

}

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path) {
	programID = loadShaders(vertex_file_path, fragment_file_path);
}

void Shader::use() {
	glUseProgram(programID);
}

void Shader::setBool(const std::string & name, bool value) const {
	glUniform1i(getLocation(name), (int)value);
}

void Shader::setInt(const std::string & name, int value) const {
	glUniform1i(getLocation(name), value);
}

void Shader::setFloat(const std::string & name, float value) const {
	glUniform1f(getLocation(name), value);
}

void Shader::setVec2(const std::string & name, glm::vec2 & value) const {
	glUniform2fv(getLocation(name), 1, &value[0]);
}

void Shader::setVec2(const std::string & name, float x, float y) const {
	glUniform2f(getLocation(name), x, y);
}

void Shader::setVec3(const std::string & name, glm::vec3 & value) const {
	glUniform3fv(getLocation(name), 1, &value[0]);
}

void Shader::setVec3(const std::string & name, float x, float y, float z) const {
	glUniform3f(getLocation(name), x, y, z);
}

void Shader::setVec4(const std::string & name, glm::vec4 & value) const {
	glUniform4fv(getLocation(name), 1, &value[0]);
}

void Shader::setVec4(const std::string & name, float x, float y, float z, float w) const {
	glUniform4f(getLocation(name), x, y, z, w);
}

void Shader::setMat2(const std::string & name, glm::mat2 & mat) const {
	glUniformMatrix2fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string & name, glm::mat3 & mat) const {
	glUniformMatrix3fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string & name, glm::mat4 & mat) const {
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
	//creating shader
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//read vertexShader from code
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);

	if (vertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << vertex_file_path << " Are you in the right directory ?" << std::endl;
		return -1;
	}

	//read fragmentShader from code
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);

	if (fragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << fragment_file_path << " Are you in the right directory ?" << std::endl;
		return -1;
	}

	//compile vertexShader
	compileShader(vertexShaderID, vertexShaderCode, vertex_file_path);
	//compile fragmentShader
	compileShader(fragmentShaderID, fragmentShaderCode, fragment_file_path);

	int result = 0;

	int infoLogLength;
	//link program
	std::cout << "linking program" << std::endl;
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//check program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		char* programErrorMessage = (char*)alloca(infoLogLength * sizeof(char));
		glGetProgramInfoLog(programID, infoLogLength, NULL, programErrorMessage);
		std::cout << programErrorMessage << std::endl;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;

}

void Shader::compileShader(unsigned int shaderID, std::string shaderCode, const char *file_path) {
	int result = 0;
	int infoLogLength;

	//compiling vertexShader
	std::cout << "Compiling shader : " <<file_path << std::endl;
	const char* vertexSourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(shaderID);

	//check vertexShader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		char* vertexShaderErrorMessage = (char*)alloca(infoLogLength * sizeof(char));
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, vertexShaderErrorMessage);
		std::cout << vertexShaderErrorMessage << std::endl;
	}
}

unsigned int Shader::getLocation(const std::string& name) const {
	return glGetUniformLocation(programID, name.c_str());
}

unsigned int Shader::getProgramID() const {
	return programID;
}

















