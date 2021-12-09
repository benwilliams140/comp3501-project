#version 330 core

#define MAX_INST_GROUPS 4
#define MAX_POSITIONS 250

// Vertex buffer
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

// Uniform (global) buffer
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat3 normal_mat;
uniform vec3[MAX_INST_GROUPS * MAX_POSITIONS] positions;
uniform int groupID;

// Attributes forwarded to the fragment shader
out vec3 position_interp;
out vec3 normal_interp;
flat out vec3 light_direction;
out vec4 color_interp;
out vec2 uv_interp;
out vec3 light_pos;

// Material attributes (constants)
uniform vec3 light_dir;

void main() {
    vec3 position = positions[groupID * MAX_POSITIONS + gl_InstanceID];
    gl_Position = projection_mat * view_mat * vec4(vertex + position, 1.0);

    position_interp = vec3(view_mat * world_mat * vec4(vertex, 1.0));
    normal_interp = vec3(view_mat * vec4(normal_mat * normal, 0.0));
    light_direction = normalize(vec3(view_mat * vec4(-light_dir, 0.0)));
    color_interp = vec4(color, 1.0);
    uv_interp = uv;
}