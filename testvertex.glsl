#version 330

uniform mat4 transformMatrix;
layout(location = 0) in vec4 vposition;
layout(location = 1) in vec2 uvTex;
out vec2 textureCoord;
out vec3 position;
out vec3 fragNormal;

void main()
{
	textureCoord = uvTex;
	position = vposition.xyz;
	fragNormal = vec3(1.0, 1.0, 1.0);
	gl_Position = transformMatrix * vposition; 
}
