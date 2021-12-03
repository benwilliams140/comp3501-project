#version 330 core

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec2 uv_interp;
in vec3 light_pos;

// Uniform (global) buffer
uniform sampler2D texture_map;

void main() {
    // Retrieve texture value
	vec4 pixel = texture(texture_map, uv_interp);
	vec3 normal = normalize(normal_interp);

	vec3 v = vec3(0,0,0); // View position
	vec3 vv = normalize(v - position_interp); // View direction
	vec3 l = vec3(-1,22,30); // Light position
	vec3 lv = normalize(l - position_interp); // Light direction (for point light)
	//vec3 lv = normalize(light_direction); // Ligth direction (for directional light)
	vec3 h = normalize((vv+lv)/2); // Halfway direction

	float diffuse = dot(normal,lv);
	float spec = max(0.0,dot(normal,h));

	spec = pow(spec,132);

    // Use texture in determining fragment colour
    gl_FragColor = pixel*(diffuse+spec+0.4);
}
