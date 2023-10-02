#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include <Objects/Object.hpp>

class Mesh {
public:
	Mesh();
	~Mesh();
	void LoadMesh(aiMesh * mesh, const aiScene * scene, std::string directory, std::map<std::string, Texture> * texturePool, bool flipTextures);
	void Render(glm::mat4 parentModelTransform, glm::mat4 view, glm::mat4 proj, unsigned int program);
	void SetupMeshInGL();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
private:
	void LoadTexturesOfType(aiMaterial* mat, aiTextureType type, std::string typeName, std::string directory, std::map<std::string, Texture> * texturePool, bool flipTextures);
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};


#endif 