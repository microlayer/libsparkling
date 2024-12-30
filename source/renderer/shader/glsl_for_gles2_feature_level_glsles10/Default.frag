#version 100
precision mediump float;

// Varying
varying vec4 color;
varying vec2 textureCoord;

// Input
uniform sampler2D uTexture0;
uniform int uDrawMode;
uniform vec3 uFontColor;

//--------------------------------------------------------------------------------------
// DrawMode = 1: Used to draw texture
// DrawMode = 2: Used to draw glyphs
//--------------------------------------------------------------------------------------
void main()
{
    if(uDrawMode == 1)
    {
        gl_FragColor = texture2D(uTexture0, textureCoord);
    }
    else if(uDrawMode == 2)
    {
        float alpha = texture2D(uTexture0, textureCoord.xy).x;
        gl_FragColor = vec4(uFontColor, alpha);
    }
    else
    {
        gl_FragColor = color;
    }
}


