#pragma once
#include <GL/glew.h>
#include "Camera.h"
#include "Mesh.h"
#include <string>
#include "GameObject.h"

class RenderEngine
{
public:
	void BindTexture(GLuint* targetTexture);
	void RenderMesh(Mesh* mesh);
	void LoadWavefront( Mesh* targetMesh, std::string path);
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	GLuint LoadTexture(const char* filename);
	static RenderEngine* Get() { static RenderEngine renderEngine; return &renderEngine; }
	std::vector<GLuint> shaderIDs;
	unsigned char* data;
	GLuint VertexArrayID;
};
