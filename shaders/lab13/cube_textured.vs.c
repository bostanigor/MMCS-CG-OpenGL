#version 330 core
uniform vec3 angle;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

mat3 rotX(float ang) { return mat3(
            1.0, 0.0, 0.0,
            0.0, cos(ang), -sin(ang),
            0.0, sin(ang),  cos(ang));
}

mat3 rotY(float ang) { return mat3(
            cos(ang), 0.0, -sin(ang),
            0.0,      1.0, 0.0,
            sin(ang), 0.0, cos(ang));
}

mat3 rotZ(float ang) { return mat3(
            cos(ang), -sin(ang), 0.0,
            sin(ang), cos(ang),  0.0,
            0.0,      0.0,       1.0);
}

void main()
{
    mat3 matr = rotX(angle.x) * rotY(angle.y) * rotZ(angle.z);

    vec3 pos = matr * aPos;

    gl_Position = vec4(pos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}