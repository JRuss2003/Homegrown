#version 330 core
in vec2 UV;
in vec3 normal;
in vec3 fragmentPos;
in vec4 vertexPos;

out vec4 final;

uniform sampler2D myTextureSampler;
uniform vec4 cameraEye;
uniform vec3 lightPos;
uniform vec3 inputLightDir;

float GetFogFactor(float d){
  float fogMax = 40.0;
  float fogMin = 1.0;
  if(d>fogMax){
    return 1;
  }
  else if(d<fogMin){
    return 0;
  }
  else{
    return 1 - (fogMax - d) / (fogMax - fogMin);
  }
}

void main(){
  float l = distance(cameraEye, vertexPos);
  float fogDensity = GetFogFactor(l);
  vec3 color = texture( myTextureSampler, UV ).rgb;
  vec3 result = mix(color, vec3(0.78, 0.78, 0.82), fogDensity);
  final = vec4(result, 1.0f);
}