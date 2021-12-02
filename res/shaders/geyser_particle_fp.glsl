#version 330 core

// Attributes passed from the vertex shader
in vec4 frag_color;
in vec2 tex_coord;

// Uniform (global) buffer
uniform sampler2D tex_samp;

uniform vec3 particle_color = vec3(1);

void main() {
    // Retrieve texture value
    vec4 pixel = texture(tex_samp, tex_coord);

    // adjust colour
    pixel = vec4(pixel.r * particle_color.r, pixel.g * particle_color.g, pixel.b * particle_color.b, sqrt(sqrt(pixel.b)) * frag_color.a);

    gl_FragColor = pixel;
}
