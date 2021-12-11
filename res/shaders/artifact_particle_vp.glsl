#version 400

const float PI = 3.1415926536;
const float PI_OVER_TWO = 1.5707963268;
const int MAX_INT = 2147483647;
const int MIN_INT = -2147483647 - 1;

// Vertex buffer
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

// Uniform (global) buffer
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 normal_mat;
uniform float velocityMultiple;
uniform float timer;

// Attributes forwarded to the geometry shader
out vec4 particle_color;
out float particle_id;

const float maxRadius = 10.0; // control the radius of the orbits
const float minRadius = 5.0;
const int particlesPerOrbit = 10;

void main() {
    particle_id = gl_InstanceID;

    int orbitIndex = gl_InstanceID % particlesPerOrbit;
    int globalIndex = int(floor(float(gl_InstanceID) / particlesPerOrbit));

    // calculate the random numbers to generate a sphere
    // mess around with the numbers a bit to get different distributions
    float radius = max(minRadius, maxRadius * mod(globalIndex * 140992091.0 + 940989061.0, 3451237613.0) / 3451237613.0);
    float u = mod(gl_InstanceID * 514101481.0 + 1000041499.0, 123459617.0) / 123459617.0;
    float v = mod(gl_InstanceID * 487141639.0 + 479001599.0, 998728351.0) / 998728351.0;
    float w = mod(gl_InstanceID * 289339937.0 + 617667649.0, 234570337.0) / 234570337.0;

    float theta = 2.0 * u * PI;
    float phi = acos(2.0 * v - 1.0);

    // update angles to "orbit" around center
    float deltaTheta = mod(globalIndex * 514101481.0 + 1000041499.0, 123459617.0) / 123459617.0;
    float deltaPhi = max(1.0, 3.0 * mod(globalIndex * 140992091.0 + 940989061.0, 3451237613.0) / 3451237613.0);

    //theta += deltaTheta * timer;
    //theta -= 0.01 * deltaTheta * orbitIndex * PI / 180.0; 

    phi += deltaPhi * timer;
    phi -= 0.01 * deltaPhi * orbitIndex * PI / 180.0; // creates the trail of particles

    // calculate the position
    vec3 position = vec3(radius * cos(theta) * sin(phi), radius * sin(phi) * sin(theta), radius * cos(phi));

    particle_color = vec4(0, 0, 0, 1.0 - 1.0 / (orbitIndex + 1));

    gl_Position = view_mat * world_mat * vec4(position, 1.0);
}