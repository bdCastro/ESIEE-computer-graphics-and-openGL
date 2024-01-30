#version 330 core
out vec4 FragColor;

uniform bool changeGradient;

void main() {
    vec4 color = vec4(1);
    vec2 uv = gl_FragCoord.xy;
    float distance = 1600.0f;
    float radius = 700.0f;

    vec2 uv_mod = mod(uv - (distance/2), distance);
    // if (length(uv_mod - (distance/2)) <= radius) {
    //     color.rgb = vec3(0.2f, 0.3f, 0.5f);
    // }

    if (changeGradient) {
        FragColor = vec4(gl_FragCoord.x / 1600.0f + 0.2f, 0.0f, gl_FragCoord.y / 1600.0f + 0.2f, 1.0f);
    } else {
        FragColor = vec4(0.2f, gl_FragCoord.y / 900.0f, gl_FragCoord.x / 1600.0f, 1.0f);
    }
}