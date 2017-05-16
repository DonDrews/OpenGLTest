#version 330

uniform mat4 transformMatrix;
layout(location = 0) in vec4 vposition;
layout(location = 1) in vec2 uvTex;
layout(location = 2) in vec3 normal;
out vec2 textureCoord;
out vec3 position;
out vec3 fragNormal;

void main()
{
	textureCoord = uvTex;
	position = vposition.xyz;
	fragNormal = normal;
	gl_Position = transformMatrix * vposition; 
}
