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

float maxSpray = 0.25;
float accel = -20.0;
float initialVelocity = 75.0;
float maxRadius = 20;
vec3 downDir = vec3(0, -1, 0);

void main() {
    particle_id = gl_InstanceID;

    // calculate the random numbers to generate a sphere
    // mess around with the numbers a bit to get different distributions
    float u = mod(gl_InstanceID * 514101481.0 + 1000041499.0, 123459617.0) / 123459617.0;
    float v = mod(gl_InstanceID * 487141639.0 + 479001599.0, 998728351.0) / 998728351.0;
    float w = mod(gl_InstanceID * 289339937.0 + 617667649.0, 234570337.0) / 234570337.0;

    float theta = 2.0 * u * PI;
    float phi = acos(2.0 * v - 1.0);
    float radius = maxRadius * w;

    // calculate normal direction (ie. outward) and particle position
    vec3 normal = normalize(vec3(cos(theta), initialVelocity * w, sin(theta)));
    vec3 position = 0.1 * normal;

    float phase = mod((timer + gl_InstanceID / 50.0), 2.0);
    vec3 velocity = vec3(initialVelocity * phase, initialVelocity + accel * phase, initialVelocity * phase);
    velocity *= velocityMultiple;
    //float velocity = initialVelocity + accel * phase;

    // calculate final position
    vec3 finalPos = vec3(vertex.x + normal.x * velocity.x * phase, vertex.y + velocity.y * phase, vertex.z + normal.z * velocity.z * phase);

    gl_Position = view_mat * world_mat * vec4(finalPos, 1.0);
}