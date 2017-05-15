#version 330

//uniform sampler2D tex;
//uniform vec3 lightPos;
//in vec2 textureCoord;
//in vec3 position;
//in vec3 fragNormal;
layout(location = 0) out vec4 FragColor;

//constants
//const float ambient = 0.2;

void main()
{
	//vec3 fragNormal = vec3(1.0, 1.0, 1.0);
	//vec3 toLight = normalize(lightPos - position);
	//float diffuse = dot(toLight, fragNormal);
	//vec3 color = vec3(1.0, 1.0, 1.0);
	//texture(tex, textureCoord).xyz;
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	//vec4(mix(color, vec3(0, 0, 0), (ambient + diffuse)), 1.0);
}
