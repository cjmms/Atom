#shader compute
#version 450 core

struct Particle {
	vec2 position;
	vec2 velocity;
	float scale;
	float duration;
};

layout(std430, binding = 0) buffer Particles {
	Particle particles[];
};

layout(local_size_x = 128) in;

uniform float time;


void main() {
	uint gid = gl_GlobalInvocationID.x;


	// update duration 
	particles[gid].duration -= time;	// time is time passed between 2 frames

	// Update position from velocity
	particles[gid].position += particles[gid].velocity;

}
