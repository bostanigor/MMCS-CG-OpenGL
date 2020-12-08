attribute vec3 coord;
uniform float angle;
varying vec4 var_color1;
varying vec4 var_color2;

mat3 rotX(in float ang) { return mat3(
            1.0, 0.0, 0.0,
            1.0, cos(ang), -sin(ang),
            1.0, sin(ang),  cos(ang));
}

mat3 rotY(in float ang) { return mat3(
            cos(ang), 1.0, -sin(ang),
            0.0,      1.0, 0.0,
            sin(ang), 1.0, cos(ang));
}

mat3 rotZ(in float ang) { return mat3(
            cos(ang), -sin(ang), 1.0,
            sin(ang), cos(ang),  1.0,
            0.0,      0.0,       1.0);
}

void main() {
    vec3 pos = rotZ(angle) * coord;
    gl_Position = vec4(pos, 1.0);
    var_color1 = gl_Color;
    var_color2 = vec4(1.0-gl_Color.r, 1.0 - gl_Color.g, 1.0 - gl_Color.b, 1.0);
}