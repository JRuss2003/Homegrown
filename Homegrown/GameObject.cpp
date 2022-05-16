#include "GameObject.h"

void GameObject::CreateObject(int x, int y, int z, GLuint* texture, std::string modelPath)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->targetTexture = texture;
	mesh.Init(this->position.x, this->position.y, this->position.z);
	mesh.LoadFromFile(modelPath);
}

void GameObject::CreateObjectFromMemory(int x, int y, int z, GLuint* texture, GLfloat* vertexData, GLfloat* uvData, GLfloat* normalData, int dataLength)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->targetTexture = texture;
	mesh.Init(this->position.x, this->position.y, this->position.z);
	mesh.LoadFromMemory(vertexData, uvData, normalData, dataLength);
}

void GameObject::Update()
{
	mesh.Update(&this->position);
}

void GameObject::Destroy()
{
	mesh.Unload();
}
