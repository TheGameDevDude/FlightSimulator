#include "VBOIndexer.h"

bool VBOIndexer::isNear(float v1, float v2) {
	return fabs(v1 - v2) < 0.01f;
}

bool VBOIndexer::getSimilarVertexIndex(glm::vec3 & in_vertex, glm::vec2 & in_uv, glm::vec3 & in_normal, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, unsigned int & result) {
	for (unsigned int i = 0; i < out_vertices.size(); i++) {
		if (isNear(in_vertex.x, out_vertices[i].x) && isNear(in_vertex.y, out_vertices[i].y) && isNear(in_vertex.z, out_vertices[i].z) &&
			isNear(in_uv.x, out_uvs[i].x) && isNear(in_uv.y, out_uvs[i].y) &&
			isNear(in_normal.x, out_normals[i].x) && isNear(in_normal.y, out_normals[i].y) && isNear(in_normal.z, out_normals[i].z)) {
			result = i;
			return true;
		}
	}
	return false;
}

void VBOIndexer::indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<unsigned int>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals) {
	for (unsigned int i = 0; i < in_vertices.size(); i++) {
		unsigned int index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);
		if (found) {
			out_indices.push_back(index);
		}
		else {
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back((unsigned int)out_vertices.size() - 1);
		}
	}
}
