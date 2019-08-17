#include "OBJLoader.h"

bool OBJLoader::loadOBJ(char const* path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals) {
	std::cout << "loading OBJ file " << path << std::endl;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::ifstream file;
	file.open(path, std::ios::in);

	char line[80];

	while (file.getline(line,80)) {
		if (line[0] == 'v' && line[1] == ' ') {
			glm::vec3 vertex;
			sscanf_s(line, "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (line[0] == 'v' && line[1] == 't') {
			glm::vec2 uv;
			sscanf_s(line, "vt %f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			glm::vec3 normal;
			sscanf_s(line, "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (line[0] == 'f') {
			int vertexIndex[3], uvIndex[3], normalIndex[3];
			sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	int k = vertexIndices.size();

	for (int i = 0; i < k; i++) {
		int vertexIndex = vertexIndices[i] - 1;
		int uvIndex = uvIndices[i] - 1;
		int normalIndex = normalIndices[i] - 1;

		out_vertices.push_back(temp_vertices[vertexIndex]);
		out_uvs.push_back(temp_uvs[uvIndex]);
		out_normals.push_back(temp_normals[normalIndex]);
	}

	file.close();
	return true;
}

