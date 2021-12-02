#version 330 core

#define POINTS_SIZE 1000

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 world_position_interp;
in vec3 normal_interp;
in vec3 light_direction;
in vec4 color_interp;
in vec2 uv_interp;

// Uniform (global) buffer
uniform sampler2D terrain_texture_1;
uniform sampler2D terrain_texture_2;
uniform sampler2D terrain_texture_3;
uniform sampler2D terrain_texture_4;
uniform vec2 points_[POINTS_SIZE];
uniform vec2 terrain_bounds;
uniform int numCells;
uniform int numPointsPerCell;

void main() {
    // Generate Worley Noise
	vec2 sPoint = mod((uv_interp * 5), 1);

    float dist = 1.0f;
    vec2 delta = 0.1 * (uv_interp - vec2(0.5));
    float d1 = distance(sPoint, points_[0]);
    float d2 = distance(sPoint, points_[1]);

    float cellSize = 1.0f / float(numCells);

    int xCell = int(floor(sPoint.x / cellSize));
    int yCell = int(floor(sPoint.y / cellSize));

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int x = xCell + i;
            int y = yCell + j;
            if(x < 0 || x > numCells || y < 0 || y > numCells) continue;

            for(int k = 0; k < numPointsPerCell; k++) {
                float tempDist = distance(sPoint, points_[(x * numCells + y) * numPointsPerCell + k]);
                if(tempDist < d1) {
                    d2 = d1;
                    d1 = tempDist;
                } else if(tempDist < d2) {
                    d2 = tempDist;
                }
            }
        }
    }

    // Calculate color from worley noise
    dist = min(100 * (d2 - d1), 0.5);
    vec3 worleyColor = vec3(dist);

    // Calculate color from terrain height
    float break1 = 0.2;
    float break2 = 0.9;
    vec3 heightColor;

    float height = world_position_interp.y;
    float heightFactor = 0 + ((1 - 0) / (terrain_bounds.y - terrain_bounds.x)) * (height - terrain_bounds.x);
    vec2 uv_coords = uv_interp * 10.0f;

    vec3 terrain_colors[] = vec3[4] (
        texture(terrain_texture_4, uv_coords).xyz,
        texture(terrain_texture_3, uv_coords).xyz,
        texture(terrain_texture_2, uv_coords).xyz,
        texture(terrain_texture_1, uv_coords).xyz
    );

    if(heightFactor >= 0 && heightFactor < break1) {
        float blendFactor = 0 + ((1 - 0) / (break1 - 0)) * (heightFactor - 0);
        heightColor = mix(terrain_colors[0], terrain_colors[1], blendFactor);
    } else if(heightFactor >= break1 && heightFactor < break2) {
        float blendFactor = 0 + ((1 - 0) / (break2 - break1)) * (heightFactor - break1);
        heightColor = mix(terrain_colors[1], terrain_colors[2], blendFactor); 
    } else if(heightFactor >= break2 && heightFactor <= 1) {
        float blendFactor = 0 + ((1 - 0) / (1 - break2)) * (heightFactor - break2);
        heightColor = mix(terrain_colors[2], terrain_colors[3], blendFactor);
    }

    // Blend worley color and height color
    vec4 pixel = vec4(mix(heightColor, worleyColor, 0.3), 1.0f);

    // Retrieve normal value
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
