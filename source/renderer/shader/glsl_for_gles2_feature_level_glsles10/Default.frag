#version 100
//precision mediump float;

// Varying
varying vec4 color;
varying vec2 textureCoord;

// Input
uniform sampler2D utexture0;
uniform int uDrawMode;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{
    if(uDrawMode == 1)
    {
	    gl_FragColor = texture(utexture0, textureCoord);        
    }
    else
    {
        gl_FragColor = color;
    }
}

