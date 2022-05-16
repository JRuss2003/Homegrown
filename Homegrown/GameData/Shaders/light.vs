#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 normal;
out vec3 fragmentPos;
uniform mat4 view;
uniform mat4 model;
uniform mat4 MVP;
uniform vec3 inputLightPos;

void main(){
  UV = vertexUV;
  normal = vertexNormal;
  normal = mat3(transpose(inverse(model))) * normal;
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
  fragmentPos = vec3(model * vec4(vertexPosition_modelspace, 1));
}