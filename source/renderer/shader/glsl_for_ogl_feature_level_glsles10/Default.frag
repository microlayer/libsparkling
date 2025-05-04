#version 130

// Varying
in vec4 color;
in vec2 textureCoord;

// Input
uniform sampler2D uTexture0;
uniform int uDrawMode;
uniform vec3 uFontColor;

// Out
out vec4 fragColor;

//--------------------------------------------------------------------------------------
// DrawMode = 1: Used to draw texture
// DrawMode = 2: Used to draw glyphs
//--------------------------------------------------------------------------------------
void main()
{
    if(uDrawMode == 1)
    {
        fragColor = texture2D(uTexture0, textureCoord);
    }
    else if(uDrawMode == 2)
    {
        float alpha = texture2D(uTexture0, textureCoord.xy).x;
        fragColor = vec4(uFontColor, alpha);
    }
    else
    {
        fragColor = color;
    }
}


