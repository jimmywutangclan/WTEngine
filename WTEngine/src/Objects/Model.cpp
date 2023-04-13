// In-house code
#include "Objects/Model.hpp"

Model::Model(std::string _id, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _offset, std::string modelLoc, std::string textureLoc):
Object(_id, _position, _rotation, _scale, _offset, textureLoc) {	
	std::ifstream infile(modelLoc, std::ifstream::in);
	std::string token;

	while (infile >> token) {
		// Recognizes v, vt and f flags(For vertex, vertex texture coord, and which vertices are in a triangle(aka index array))
	}

}