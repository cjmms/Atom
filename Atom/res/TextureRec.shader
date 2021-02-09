#shader vertex
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTextureCoord;

out vec2 TextureCoord;

uniform vec2 scale;
uniform vec2 pos;

void main()
{
	// make sure the left top vertex is at origin
	vec2 position = vec2(abs(aPos.x), -abs(aPos.y)) + aPos.xy;

	// scale
	position = scale * position;

	// translate
	position = pos + position;

	gl_Position = vec4(position, 0.0, 1.0);
	TextureCoord = aTextureCoord;
}







#shader fragment
#version 430 core

in vec2 TextureCoord;
out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, TextureCoord);
}