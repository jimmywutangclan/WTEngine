#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Objects/mesh.hpp>

#include <string>
#include <iostream>
#include <vector>

class GameObject {
public:
	GameObject();
	~GameObject();
	void FromModelFile(std::string dir);
	void ProcessSceneNode(aiNode* node, const aiScene* scene);

	std::vector<GameObject*> children;
private:
};

#endif