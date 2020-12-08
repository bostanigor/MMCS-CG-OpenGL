varying vec4 var_color1;
varying vec4 var_color2;

void main() {
    if (gl_FrontFacing) // is the fragment part of a front face?
    {
        gl_FragColor = var_color1;
    }
    else // fragment is part of a back face
    {
        gl_FragColor = var_color2;
    }
}