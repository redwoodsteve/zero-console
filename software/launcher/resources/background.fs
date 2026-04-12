/*#version 110

varying vec2 fragTexCoord;
varying vec4 fragColor;

void main() {
	vec3 stop1 = vec3(0.051, 0.106, 0.165);
	vec3 stop2 = vec3(0.106, 0.149, 0.231);

	float steps = 5.0;

	float pos = floor(fragTexCoord.y*fragTexCoord.x * steps) / steps;

	gl_FragColor = vec4(mix(stop1, stop2, pos), 1);
}*/
#version 110

varying vec2 fragTexCoord;

// This matrix determines the threshold for each pixel in a 4x4 block
float bayer4(vec2 uv) {
    vec2 b = floor(mod(uv, 4.0));
    int x = int(b.x);
    int y = int(b.y);
    
    // 4x4 Bayer Matrix values
    if (y == 0) { if (x == 0) return 0.0625; if (x == 1) return 0.5625; if (x == 2) return 0.1875; return 0.6875; }
    if (y == 1) { if (x == 0) return 0.8125; if (x == 1) return 0.3125; if (x == 2) return 0.9375; return 0.4375; }
    if (y == 2) { if (x == 0) return 0.2500; if (x == 1) return 0.7500; if (x == 2) return 0.1250; return 0.6250; }
    if (y == 3) { if (x == 0) return 1.0000; if (x == 1) return 0.5000; if (x == 2) return 0.8750; return 0.3750; }
    return 0.0;
}

void main() {
    vec3 stop1 = vec3(0.051, 0.106, 0.165);
    vec3 stop2 = vec3(0.106, 0.149, 0.331);

    float numSteps = 4.0;
    float pos = fragTexCoord.y;

    // 1. Calculate the threshold for this specific pixel
    // We use raw pixel coordinates (fragTexCoord * canvasSize)
    // Note: You might need to pass in your canvas resolution as a uniform for perfect alignment
    float threshold = bayer4(gl_FragCoord.xy);

    // 2. Add the dither threshold to the smooth gradient position
    // This makes some pixels "jump" to the next step earlier than others
    float ditheredPos = pos + (threshold / numSteps);

    // 3. Quantize the position
    float finalPos = floor(ditheredPos * numSteps) / numSteps;

    gl_FragColor = vec4(mix(stop1, stop2, finalPos), 1.0);
}