attribute vec3 coord;
uniform float angle;
varying vec4 var_color;

mat3 rotX(in float ang) { return mat3(
            1.0, 0.0, 0.0,
            1.0, cos(ang), -sin(ang),
            1.0, sin(ang),  cos(ang));
}

void main() {
    vec3 pos = rotX(angle)*coord;
    gl_Position = vec4(pos, 1.0);
    var_color = gl_Color;
}