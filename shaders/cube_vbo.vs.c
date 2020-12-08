attribute vec3 coordinate;
attribute vec3 vertex_color;
uniform	vec3 angle;

void main() {
    float x_sin = sin(angle.x);
    float x_cos = cos(angle.x);

    float y_sin = sin(angle.y);
    float y_cos = cos(angle.y);

    float z_sin = sin(angle.z);
    float z_cos = cos(angle.z);

    vec3 rot_y = coordinate * mat3(y_cos, 0, y_sin, 0, 1, 0, -y_sin, 0, y_cos);
    vec3 rot_x = rot_y * mat3(1, 0, 0, 0, x_cos, x_sin,  0, -x_sin, x_cos);
    vec3 rot_z = rot_x * mat3(z_cos,  z_sin, 0, -z_sin, z_cos,  0,0, 0, 1);
    
    gl_Position = vec4(rot_z, 1.0);
    gl_FrontColor = vec4(vertex_color, 1.0);
}