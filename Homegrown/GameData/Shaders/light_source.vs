#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 MVP;
uniform vec3 lightPos;

void main(){
  UV = vertexUV;
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
}