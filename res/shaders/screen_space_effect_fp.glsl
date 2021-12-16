#version 330 core

// Attributes passed from the vertex shader
in vec2 uv0;

// Uniform (global) buffer
uniform sampler2D texture_map;
uniform sampler2D blood_texture_map;
uniform float timer;
uniform float stun_start_time;
uniform float stun_max_time;
uniform float blood_start_time;
uniform float blood_max_time;

// Forward declaration
float random(int ID);

void main() {
    // Retrieve texture value
    vec4 pixel = texture(texture_map, uv0);
    vec3 finalPixel = pixel.xyz;

    // Do the stun effect
    if(stun_start_time > 0) {
        vec2 shakePos;
        shakePos.x = uv0.x + 0.01 * cos(20*timer) * (stun_start_time/stun_max_time);
        shakePos.y = uv0.y;

        vec4 defaultPixel = texture(texture_map, shakePos);
        vec2 pos1 = shakePos; vec2 pos2 = shakePos; vec2 pos3 = shakePos;
        int randID = int(timer * 1000000000);

        pos1.x = pos1.x + 0.01*(sin(timer*3.0+(random(randID+35432))*pos1.y));
        pos1.y = pos1.y + 0.01*(cos(timer*3.0+(random(randID+45434))*pos1.x));
        vec4 shift1Pixel = texture(texture_map, pos1);

        pos2.x = pos2.x + 0.0496*(cos(timer*5.0+(random(randID+8323))*pos2.y));
        pos2.y = pos2.y + 0.0496*(sin(timer*5.0+(random(randID+5391))*pos2.x));
        vec4 shift2Pixel = texture(texture_map, pos2);

        pos3.x = pos3.x + 0.0065*(sin(timer*4.0+(random(randID+9865))*pos3.y));
        pos3.y = pos3.y + 0.0065*(cos(timer*4.0+(random(randID+3924))*pos3.x));
        vec4 shift3Pixel = texture(texture_map, pos3);

        vec3 stunnedPixel = (shift1Pixel.xyz + shift2Pixel.xyz + shift3Pixel.xyz) / 3;
        finalPixel = mix(stunnedPixel, defaultPixel.xyz, 0.7 * 1-(stun_start_time/stun_max_time));
    }

    // Do the blood effect
    if(blood_start_time > 0) {
        vec4 blood_pixel = texture(blood_texture_map, uv0);
        finalPixel += (blood_pixel.xyz * blood_pixel.a * (blood_start_time/blood_max_time));
    }

    // Use texture in determining fragment colour
    gl_FragColor = vec4(finalPixel, 1.0);
}

float random(int ID) {
	return float((ID * 177211 + 15523111) % 722417) / 722417; 
}