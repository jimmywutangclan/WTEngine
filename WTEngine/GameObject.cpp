#include "Objects/GameObject.hpp"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::FromModelFile(std::string dir) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(dir, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << importer.GetErrorString() << std::endl;
		return;
	}

	std::string directory = dir.substr(0, dir.find_last_of("/"));

	ProcessSceneNode(scene->mRootNode, scene);
}

void GameObject::ProcessSceneNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		Mesh* newMesh = new Mesh();
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		GameObject * newObject = new GameObject();
		newObject->ProcessSceneNode(node->mChildren[i], scene);
		children.push_back(newObject);
	}
}

