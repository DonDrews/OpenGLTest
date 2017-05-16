#version 330

uniform sampler2D tex;
uniform vec3 lightDir;
in vec2 textureCoord;
in vec3 position;
in vec3 fragNormal;
layout(location = 0) out vec4 FragColor;

//constants
const float ambient = 0.2;

void main()
{
	float diffuse = dot(-normalize(lightDir), fragNormal);
	vec3 color = texture(tex, textureCoord).xyz;
	FragColor = vec4(mix(color, vec3(1, 1, 1), (ambient + diffuse)), 1.0);
}
