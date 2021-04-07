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
uniform float seed;
uniform vec2 spawnCenter;

float rand(vec2 co) {
	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}


float PHI = 1.61803398874989484820459;  //  Golden Ratio   

float gold_noise(in vec2 xy, in float seed) {
	return fract(tan(distance(xy * PHI, xy) * seed) * xy.x);
}


void main() {
	uint gid = gl_GlobalInvocationID.x;


	// update duration 
	particles[gid].duration -= time;	// time is time passed between 2 frames

	// Update position from velocity
	particles[gid].position += particles[gid].velocity;

	if (particles[gid].duration < 0)
	{
		particles[gid].duration = gold_noise(vec2(0.0001, 1.0), seed);
		particles[gid].position = spawnCenter;
	}

}



