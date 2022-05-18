#include "RenderEngine.h"
#include "Game.h"
#include "GameObject.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "Textures.h"
void RenderEngine::Init()
{
	glGenVertexArrays(1, &RenderEngine::Get()->VertexArrayID);
}

void RenderEngine::BindTexture(GLuint* targetTexture)
{
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, *targetTexture);
}

void RenderEngine::RenderMesh(Mesh* mesh)
{
	//Passing parameters to the shader
	glm::vec3 lightPos = glm::vec3(30, 20, 30);
	glUniformMatrix4fv(Camera::Get()->MatrixID, 1, GL_FALSE, &mesh->mvp[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*mesh->targetShader, "model"), 1, GL_FALSE, &mesh->model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*mesh->targetShader, "view"), 1, GL_FALSE, &Camera::Get()->view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*mesh->targetShader, "projection"), 1, GL_FALSE, &Camera::Get()->projection[0][0]);
	glUniform3fv(glGetUniformLocation(*mesh->targetShader, "lightPos"), 1, &lightPos[0]);
	glUniformMatrix4fv(glGetUniformLocation(*mesh->targetShader, "cameraEye"), 1, GL_FALSE, &Camera::Get()->view[0][0]);
	//Do normal render stuff with varrays ,normals, uvs and vertex
	glBindVertexArray(VertexArrayID);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->normalbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void RenderEngine::LoadWavefront(Mesh* targetMesh, std::string path)
{
	//Data vectors
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> uvData;
	std::vector<glm::vec3> normalData;
	//Index buffers for each data vector
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	char lineHeader[128];
	float x, y, z;
	FILE* file = fopen(path.c_str(), "r");
	while (1) {
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		//if vertex
		if (strcmp(lineHeader, "v") == 0) {

			fscanf(file, "%f %f %f\n", &x, &y, &z);
			vertexData.push_back(glm::vec3(x, y, z));
		}
		//if uv
		else if (strcmp(lineHeader, "vt") == 0) {
			fscanf(file, "%f %f\n", &x, &y);
			uvData.push_back(glm::vec2(x, y));
		}
		//if normal
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			normalData.push_back(glm::vec3(x, y, z));
		}
		else if (strcmp(lineHeader, "f") == 0) {
			int matches;
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			if(normalData.size() < 1)
				matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
			else
				matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

		}
	}

	fclose(file);
	glm::vec3 vertex;

	for (int x = 0; x < vertexIndices.size(); x++) {
		vertex = vertexData[vertexIndices[x] - 1];
		targetMesh->vertexData.push_back(vertex);
	}

	for (int x = 0; x < uvIndices.size(); x++) {
		targetMesh->uvData.push_back(uvData[uvIndices[x] - 1]);
	}
	
	for (int x = 0; x < normalIndices.size(); x++) {
		targetMesh->normalData.push_back(normalData[normalIndices[x] - 1]);
	}
}


GLuint RenderEngine::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	//GLint Result = GL_FALSE;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID;
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	shaderIDs.push_back(ProgramID);
	return 0;
}

GLuint RenderEngine::LoadTexture(const char* filename)
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	//unsigned char* data;

	FILE* file = fopen(filename, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54;

	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	return textureID;
}
