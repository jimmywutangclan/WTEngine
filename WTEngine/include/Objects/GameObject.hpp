#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <Objects/mesh.hpp>

#include <string>
#include <iostream>
#include <vector>

class GameObject {
public:
	GameObject();
	~GameObject();
	void FromModelFile(std::string dir, bool flatten, std::map<std::string, Texture> * texturePool);
	void ProcessSceneNode(aiNode* node, const aiScene* scene, std::string directory, bool flatten, std::map<std::string, Texture> * texturePool);
	void Render(glm::mat4 view, glm::mat4 proj, unsigned int program);

	std::vector<GameObject*> children;
private:
	std::vector<Mesh*> meshes;
};

#endif