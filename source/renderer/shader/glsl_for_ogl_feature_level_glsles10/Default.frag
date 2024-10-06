#version 130

// Varying
in vec4 color;
in vec2 textureCoord;

// Input
uniform sampler2D utexture0;
uniform int uDrawMode;

// Out
out vec4 fragColor;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{
    if(uDrawMode == 1)
    {
        fragColor = texture2D(utexture0, textureCoord);
    }
    else
    {
        fragColor = color;
    }
}


