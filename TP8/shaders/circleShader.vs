#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform int hexagon;
uniform float angle;

vec2 rotate_around_point(vec2 point, vec2 center, float angle) {
   vec2 translated = point - center;
   mat2x2 rotation = mat2x2(cos(angle), -sin(angle), sin(angle), cos(angle));
   point = translated * rotation;

   return point + center;
}

void main() {
   vec3 scaleDown = vec3(0.5f);

   vec2 result = aPos.xy;

   if (hexagon == 0) {
      vec2 center = vec2(-0.95f/2.0f, 0.80f/2.0f);
      result = rotate_around_point(aPos.xy, center, angle);
   } else if (hexagon == 1) {
      vec2 center = vec2(0.95f/2.0f, 0.80f/2.0f);
      result = rotate_around_point(aPos.xy, center, -angle);
   } else {
      vec2 center = vec2(0.0f, -0.80f/2.0f);
      result = rotate_around_point(aPos.xy, center, angle);
      result = result - center;
      result = result * cos(angle);
      result = result + center;
   }

   gl_Position = vec4(result, 1.0f, 1.0f);
   TexCoord = aTexCoord;
}