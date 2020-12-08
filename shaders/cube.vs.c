attribute vec3 coordinate;
uniform	vec3 angle;

void main() {
    float x_sin = sin(angle.x);
    float x_cos = cos(angle.x);

    float y_sin = sin(angle.y);
    float y_cos = cos(angle.y);

    float z_sin = sin(angle.z);
    float z_cos = cos(angle.z);
    
    vec3 rot_y = vec3(coordinate.x * y_cos + coordinate.z * y_sin,  coordinate.y, coordinate.z * y_cos - coordinate.x * y_sin);
    vec3 rot_x = vec3(rot_y.x,  rot_y.y * x_cos + rot_y.z * x_sin, rot_y.z * x_cos - rot_y.y * x_sin);
    vec3 rot_z = vec3(rot_x.x * z_cos - rot_x.y * z_sin,  rot_x.y * z_cos + rot_x.x * z_sin, rot_x.z);

    gl_Position = vec4(rot_z, 1.0);
    gl_FrontColor = gl_Color;
}