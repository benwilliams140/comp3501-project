#version 330 core

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
uniform mat4 uv_mat;

// Attributes forwarded to the fragment shader
out vec3 position_interp;
out vec3 normal_interp;
out vec4 color_interp;
out vec2 uv_interp;
flat out vec3 light_direction;

// Material attributes (constants)
uniform vec3 light_dir;

void main() {
    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);

    position_interp = vec3(view_mat * world_mat * vec4(vertex, 1.0));
    normal_interp = vec3(view_mat * vec4(normal_mat * normal, 0.0));
    light_direction = normalize(vec3(view_mat * vec4(-light_dir, 0.0)));
    color_interp = vec4(color, 1.0);
    uv_interp = vec4(uv_mat * vec4(uv, 0.0, 1.0)).xy;
}
