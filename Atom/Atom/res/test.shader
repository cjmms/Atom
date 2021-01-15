#shader vertex
#version 430 core
layout(location = 0) in vec3 aPos;

uniform vec2 scale;
uniform vec2 pos;

void main()
{
	vec2 position = vec2( abs(aPos.x), -abs(aPos.y)) + aPos.xy;
	position = scale * position;

	position = pos + position;

	gl_Position = vec4(position, 0.0, 1.0);
}

#shader fragment
#version 430 core
out vec4 FragColor;


void main()
{
	FragColor = vec4(1.0, 0.4, 0.6, 1.0f);
}