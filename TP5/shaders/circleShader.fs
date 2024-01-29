#version 330 core
out vec4 FragColor;
void main() {
    vec4 color = vec4(1);
    vec2 uv = gl_FragCoord.xy;
    float distance = 145.0f;
    float radius = 50.0f;

    vec2 uv_mod = mod(uv - (distance/2), distance);
    if (length(uv_mod - (distance/2)) <= radius) {
        color.rgb = vec3(0.2f, 0.3f, 0.5f);
    }

    FragColor = color;
}