#shader vertex
#version 430 core
layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}







#shader fragment
#version 430 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
    color = vec4(1.0, 0.0, 0.0, 1.0);
}