#include "Mesh.h"
#include "Camera.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "RenderEngine.h"

void Mesh::Init(float x, float y, float z)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
}

void Mesh::AddIndex(int index)
{
	/*
	if (indices.size() < 1) {
		indices.push_back(index);
	}
	else {
		for (int x = 0; x < index; x++) {
			if (normalData.size() > 0 && (this->vertexData[x] == this->vertexData[index] && this->normalData[x] == this->normalData[index] && this->uvData[x] == this->uvData[index])) {
				indices.push_back(x);
				return;
			}
			else if (this->vertexData[x] == this->vertexData[index] && this->uvData[x] == this->uvData[index]) {
				indices.push_back(x);
				return;
			}
		}
		indices.push_back(index);
	}
	*/
	indices.push_back(index);
}

void Mesh::LoadFromMemory(GLfloat* vertexData, GLfloat* uvData, GLfloat* normalData, int dataLength)
{
	for (int i = 0; i < dataLength * 3; i++) {
		if (i % 3 == 0)
			this->vertexData.push_back(glm::vec3(*vertexData, *(vertexData + 1), *(vertexData + 2)));
		vertexData++;
	}
	for (int i = 0; i < dataLength * 2; i++) {
		if (i % 2 == 0)
			this->uvData.push_back(glm::vec2(*uvData, *(uvData + 1)));
		uvData++;
	}
	for (int i = 0; i < dataLength * 3; i++) {
		if (i % 3 == 0)
			this->normalData.push_back(glm::vec3(*normalData, *(normalData + 1), *(normalData + 2)));
		vertexData++;
	}
	for (int i = 0; i < dataLength; i++) {
		AddIndex(i);
	}

	glBindVertexArray(RenderEngine::Get()->VertexArrayID);
	//Load vertex data
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(glm::vec3), &this->vertexData[0], GL_STATIC_DRAW);

	//Load uv data
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->uvData.size() * sizeof(glm::vec2), &this->uvData[0], GL_STATIC_DRAW);

	//Load normal data
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->normalData.size() * sizeof(glm::vec3), &this->normalData[0], GL_STATIC_DRAW);

	//Load index data
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Mesh::LoadFromFile(std::string path)
{
	RenderEngine::Get()->LoadWavefront(this, path);
	for (int i = 0; i < this->vertexData.size(); i++) {
		AddIndex(i);
	}
	
	//glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(RenderEngine::Get()->VertexArrayID);
	//Load vertex data
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(glm::vec3), &this->vertexData[0], GL_STATIC_DRAW);

	//Load uv data
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->uvData.size() * sizeof(glm::vec2), &this->uvData[0], GL_STATIC_DRAW);

	//Load normal data
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->normalData.size() * sizeof(glm::vec3), &this->normalData[0], GL_STATIC_DRAW);

	//Load index data
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Mesh::Unload()
{
	//Free buffers
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	//glDeleteVertexArrays(1, &VertexArrayID);
	//Free vectors, since clearing them doesnt free the memory apparently :s
	vertexData.clear();
	vertexData.shrink_to_fit();
	uvData.clear();
	uvData.shrink_to_fit();
	normalData.clear();
	normalData.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
}

void Mesh::Update(glm::vec3* parentPos)
{
	model = glm::translate(glm::mat4(1.0f), *parentPos) * glm::toMat4(this->angleQuat);
	mvp = Camera::Get()->projection * Camera::Get()->view * model;
}

void Mesh::MoveTo(float x, float y, float z, glm::vec3* parentPos)
{
	this->model = glm::translate(this->model, *parentPos);
	this->model = glm::translate(this->model, glm::vec3(x, y, z));
}

void Mesh::RotateTo(float angle, float meshangle)
{
	this->angleQuat = glm::rotate(glm::toMat4(this->angleQuat), -(meshangle), glm::vec3(0.0f, 1.0f, 0.0f));
	this->angleQuat = glm::rotate(glm::toMat4(this->angleQuat), (angle), glm::vec3(0.0f, 1.0f, 0.0f));
}

