uniform vec4 color1;
uniform vec4 color2;

void main() {
    if (mod(gl_FragCoord.x, 10)<5.0 ^^ mod(gl_FragCoord.y, 10)<5.0)
        gl_FragColor = color1;
    else
        gl_FragColor = color2;
}