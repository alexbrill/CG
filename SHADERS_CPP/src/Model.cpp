
#include "include/Model.h"

Model::Model(const GLchar *filename) : verts(), faces(), norms(){
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	if (in.fail()) return;
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			glm::vec3 v;
			for (GLuint i = 0; i < 3; i++) iss >> v[i];
			verts.push_back(v);
		}
		else if (!line.compare(0, 4, "vn  ")) {
			iss >> trash;
			glm::vec3 v;
			for (GLuint i = 0; i < 3; i++) iss >> v[i];
			norms.push_back(v);
		}
		else if (!line.compare(0, 2, "f ")) {
			std::vector<GLuint> f;
			GLuint itrash, idx;
			iss >> trash;
			while (iss >> idx >> trash >> itrash >> trash >> itrash) {
				idx--; // in wavefront obj all indices start at 1, not zero
				faces.push_back(idx);
			}
			//faces.push_back(f);
		}
	}
	std::cerr << "# v# " << verts.size() << " f# " << faces.size() << std::endl;
}

Model::~Model() {
}

GLuint Model::nverts() {
	return (GLuint)verts.size();
}

GLuint Model::nfaces() {
	return (GLuint)faces.size();
}

GLuint Model::face(GLuint idx) {
	return faces[idx];
}

glm::vec3 Model::vert(GLuint i) {
	return verts[i];
}


