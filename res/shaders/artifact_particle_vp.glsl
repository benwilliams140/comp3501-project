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

const float maxSpray = 0.25;
const float trad = 0.125;

void main() {
    particle_id = gl_InstanceID;

    float phase = (gl_InstanceID % 10) / 10.0;

    // calculate the random numbers to generate a sphere
    float u = mod(gl_InstanceID * 514101481.0 + 1000041499.0, 123459617.0) / 123459617.0;
    float v = mod(gl_InstanceID * 487141639.0 + 479001599.0, 998728351.0) / 998728351.0;
    float w = mod(gl_InstanceID * 289339937.0 + 617667649.0, 234570337.0) / 234570337.0;

    // calculate angles and radius
    float theta = 2.0 * u * PI;
    float phi = acos(2.0 * v - 1.0);
    float spray = maxSpray * pow(w, float(1.0 / 3.0));

    // calculate normal direction (ie. outward) and particle position
    vec3 normal = vec3(spray * cos(theta) * sin(phi), spray * sin(theta) * sin(phi), spray*cos(phi));
    vec3 position = trad * normal;

    // use time to move particles
    float multiple = mod(4 * timer * phase, 3.0) + 1.0;

    // calculate final position
    vec3 finalPos = vertex + multiple * 75 * position;
    gl_Position = view_mat * world_mat * vec4(finalPos, 1.0);

    // set alpha based on distance to center
    float dist = length(finalPos - vertex);
    particle_color = vec4(0, 0, 0, 1.0);
}