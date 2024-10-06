#version 100
precision mediump float;

// Varying
varying vec4 color;
varying vec2 textureCoord;

// Input
uniform sampler2D uTexture0;
uniform int uDrawMode;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{
    if(uDrawMode == 1)
    {
        gl_FragColor = texture2D(uTexture0, textureCoord);
    }
    else
    {
        gl_FragColor = color;
    }
}


