#shader vertex
#version 430 core
layout(location = 0) in vec3 aPos;

uniform vec2 scale;
uniform vec2 pos;

uniform vec2 cameraPos;
uniform mat4 projection;


void main()
{
	// make sure the center is at origin
	vec2 position = aPos.xy;

	// scale
	position = scale * position;

	// translate
	position = pos + position - cameraPos;

	gl_Position = projection * vec4(position, 0.0, 1.0);
}







#shader fragment
#version 430 core
out vec4 FragColor;

uniform vec3 color;
uniform int wireframe;

uniform float alpha;

void main()
{
	FragColor = vec4(color, alpha);
	if (wireframe == 1) FragColor = vec4(1.0, 0.0, 0.0, alpha);
}