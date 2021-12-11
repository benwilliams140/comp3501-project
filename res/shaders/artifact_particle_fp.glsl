#version 330 core

// Attributes passed from the vertex shader
in vec4 frag_color;
in vec2 tex_coord;

// Uniform (global) buffer
uniform sampler2D tex_samp;

uniform vec3 particle_color = vec3(1);

// Simulation parameters (constants)
uniform vec3 object_color = vec3(0.6, 0.2, 0.01);

void main() {
    // Retrieve texture value
    vec4 pixel = texture(tex_samp, tex_coord);

    // adjust colour
    pixel = vec4(pixel.r * particle_color.r, pixel.g * particle_color.g, pixel.b * particle_color.b, sqrt(pixel.r));

    // Get pixel from texture
    vec4 outval = texture(tex_samp, tex_coord);
    // Adjust specified object color according to the grayscale texture value
    outval = vec4(outval.r*object_color.r, outval.g*object_color.g, outval.b*object_color.b, sqrt(sqrt(outval.r))*frag_color.a);
    // Set output fragment color
    gl_FragColor = outval;

    /*if(pixel.a <= 0.1) {
        discard;
    }*/

    //gl_FragColor = pixel;
    //gl_FragColor = vec4(particle_color, frag_color.a);
}