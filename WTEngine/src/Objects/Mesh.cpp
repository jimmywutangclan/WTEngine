#include "Objects/Mesh.hpp"

unsigned int TextureFromFile(std::string fileName, std::string dir, bool flipTextures);

Mesh::Mesh() {

}

Mesh::~Mesh() {

}

void Mesh::LoadMesh(aiMesh* mesh, const aiScene* scene, std::string directory, std::map<std::string, Texture> * texturePool, bool flipTextures)
{
	bool meshHasTexture = mesh->mTextureCoords[0];
	for (int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoords;
		aiVector3D* origPos = &mesh->mVertices[i];
		aiVector3D* origNormal = &mesh->mNormals[i];
		pos.x = origPos->x;
		pos.y = origPos->y;
		pos.z = origPos->z;
		normal.x = origNormal->x;
		normal.y = origNormal->y;
		normal.x = origNormal->z;
		if (meshHasTexture) {
			texCoords.x = mesh->mTextureCoords[0][i].x;
			texCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			texCoords.x = 0;
			texCoords.y = 0;
		}
		Vertex v;
		v.pos = pos;
		v.normal = normal;
		v.texcoords = texCoords;
		vertices.push_back(v);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace* face = &mesh->mFaces[i];
		for (unsigned int j = 0; j < face->mNumIndices; j++) {
			indices.push_back(face->mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex > 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		LoadTexturesOfType(material, aiTextureType_DIFFUSE, "texture_diffuse", directory, texturePool, flipTextures);
		LoadTexturesOfType(material, aiTextureType_SPECULAR, "texture_specular", directory, texturePool, flipTextures);
	}
	SetupMeshInGL();
}

void Mesh::SetupMeshInGL() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

	glBindVertexArray(0);
}

void Mesh::Render(glm::mat4 parentModelTransform, glm::mat4 view, glm::mat4 proj, unsigned int program) {
	unsigned int modelLoc = glGetUniformLocation(program, "model");
	unsigned int viewLoc = glGetUniformLocation(program, "view");
	unsigned int projLoc = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(parentModelTransform));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glUseProgram(program);

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		glUniform1i(glGetUniformLocation(program, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::LoadTexturesOfType(aiMaterial * mat, aiTextureType type, std::string typeName, std::string directory, std::map<std::string, Texture> * texturePool, bool flipTextures) {
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		if (texturePool->find(str.C_Str()) == texturePool->end()) {
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory, flipTextures);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texturePool->insert(std::make_pair(str.C_Str(), texture));
		}
		else {
			Texture second = texturePool->find(str.C_Str())->second;
			Texture toAdd;
			toAdd.id = second.id;
			toAdd.type = second.type;
			toAdd.path = second.path;
			textures.push_back(toAdd);
		}
	}
}

unsigned int TextureFromFile(std::string fileName, std::string dir, bool flipTextures) {
	std::string path = dir + "/" + fileName;
	std::cout << path << std::endl;
	int width, height, nrChannels;
	if (flipTextures) {
		stbi_set_flip_vertically_on_load(true);
	}
	unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (flipTextures) {
		stbi_set_flip_vertically_on_load(false);
	}
	if (!textureData) {
		std::cout << "Texture loading error" << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum format;
	if (nrChannels == 1) {
		format = GL_RED;
	}
	else if (nrChannels = 3) {
		format = GL_RGB;
	}
	else if (nrChannels = 4) {
		format = GL_RGBA;
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(textureData);

	return texture;
}