#include "Objects/GameObject.hpp"

GameObject::GameObject(std::string _name) {
	name = _name;
}

GameObject::~GameObject() {

}

void GameObject::FromModelFile(std::string dir, bool flatten, std::map<std::string, Texture> * texturePool, bool flipTextures) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(dir, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << importer.GetErrorString() << std::endl;
		return;
	}

	std::string directory = dir.substr(0, dir.find_last_of("/"));

	ProcessSceneNode(scene->mRootNode, scene, directory, flatten, texturePool, flipTextures);
}

void GameObject::ProcessSceneNode(aiNode* node, const aiScene* scene, std::string directory, bool flatten, std::map<std::string, Texture>* texturePool, bool flipTextures) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		Mesh* newMesh = new Mesh();
		newMesh->LoadMesh(scene->mMeshes[node->mMeshes[i]], scene, directory, texturePool, flipTextures);
		meshes.push_back(newMesh);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		if (flatten) {
			ProcessSceneNode(node->mChildren[i], scene, directory, flatten, texturePool, flipTextures);
		}
		else {
			GameObject* newObject = new GameObject(name + " child " + std::to_string(i));
			newObject->ProcessSceneNode(node->mChildren[i], scene, directory, flatten, texturePool, flipTextures);
			children.push_back(newObject);
		}
	}
}

void GameObject::Render(glm::mat4 view, glm::mat4 proj, unsigned int program) {
	glm::mat4 model(1.0f);
	
	for (Mesh * mesh : meshes) {
		mesh->Render(model, view, proj, program);
	}
	for (GameObject* child : children) {
		child->Render(view, proj, program);
	}
}

