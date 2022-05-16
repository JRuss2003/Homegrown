#version 330 core
in vec2 UV;
in vec3 normal;
in vec3 fragmentPos;
uniform vec3 lightPos;
uniform vec3 inputLightDir;
out vec4 final;
uniform sampler2D myTextureSampler;

void main(){
  vec3 lightColor = vec3(0.99f, 0.98f, 0.92f);
  vec3 lightDir = normalize(lightPos - fragmentPos); 
  float ambientStrength = 0.2f;
  vec3 ambient = ambientStrength * lightColor;
  vec3 norm = normalize(normal);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = diff * lightColor;
  vec3 color = texture( myTextureSampler, UV ).rgb;
  vec3 result = (ambient + diffuse) * color;
  final = vec4(result, 1.0f);
}