#version 130

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec2 uv_interp;
in vec3 light_pos;

// Uniform (global) buffer
uniform sampler2D texture_map;
uniform float timer; 

void main() 
{
    // Remove this code and replace with your own.

    float red = uv_interp.x;
    float green = uv_interp.y;
    float blue = timer*0.25; // slowly increase blue over time
	// Note, colors are in the range 0-1.
	// What happens when time goes up above 4 seconds?

    vec4 outcol = vec4(red,green,blue,1.0);
	

    gl_FragColor = outcol;
}
