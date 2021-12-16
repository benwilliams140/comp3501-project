#version 330 core

// Attributes passed from the vertex shader
in vec2 uv0;

// Uniform (global) buffer
uniform sampler2D texture_map;
uniform sampler2D blood_texture_map;
uniform float start_time;
uniform float max_time;

void main() {
    // Retrieve texture value
    vec4 pixel1 = texture(texture_map, uv0);
    vec4 pixel2 = texture(blood_texture_map, uv0);
    vec3 finalColor = pixel1.xyz + (pixel2.xyz * pixel2.a * (start_time/max_time));

    // Use texture in determining fragment colour
    gl_FragColor = vec4(finalColor, 1.0);
}
