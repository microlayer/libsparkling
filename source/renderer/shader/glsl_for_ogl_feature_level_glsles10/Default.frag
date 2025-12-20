#version 130

// Varying
in vec4 color;
in vec4 vertexNormal;
in vec2 textureCoord;
in vec3 lightDirection;

// Input
uniform sampler2D uTexture0;
uniform int uDrawMode;
uniform vec3 uFontColor;

// Out
out vec4 fragColor;

//--------------------------------------------------------------------------------------
// uDrawMode (uniform) sets the draw mode for this draw call.
// DrawMode = 1: Used to draw texture
// DrawMode = 2: Used to draw glyphs
// DrawMode = 3: Used to draw Normal Vector Debug Visualization for mesh
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
    else if(uDrawMode == 3)
    {
        vec3 n = normalize(vertexNormal.xyz);
        fragColor = vec4(n * 0.5 + 0.5, 1.0);
    }
    else
    {
        fragColor = color;
    }
}


