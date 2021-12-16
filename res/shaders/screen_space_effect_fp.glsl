#version 330 core

// Attributes passed from the vertex shader
in vec2 uv0;

// Uniform (global) buffer
uniform sampler2D texture_map;

void main() {
    // Retrieve texture value
    vec4 pixel = texture(texture_map, uv0);

    // Use texture in determining fragment colour
    gl_FragColor = pixel;
}
