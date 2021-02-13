#shader vertex
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTextureCoord;

out vec2 TextureCoord;

uniform vec2 scale;
uniform vec2 pos;

uniform vec2 cameraPos;

void main()
{
	// make sure the center is at origin
	vec2 position = aPos.xy;

	// scale
	position = scale * position;

	// translate
	position = pos + position - cameraPos;

	gl_Position = vec4(position, 0.0, 1.0);
	TextureCoord = aTextureCoord;
}







#shader fragment
#version 430 core

in vec2 TextureCoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform int wireframe;

void main()
{
	FragColor = texture(tex, TextureCoord);
	if (wireframe == 1) FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}