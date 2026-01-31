#version 130

// Varying
in vec4 color;
in vec3 vertexNormal;
in vec2 textureCoord;
in vec3 lightDirection;
in vec3 barycentric;

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
// DrawMode = 4: Used to draw mesh with each triangle filled using its barycenter RGB color
// DrawMode = 5: Used to draw mesh as wireframe
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
    else if(uDrawMode == 4)
    {
        fragColor = vec4(barycentric, 1.0);
    }
    else if(uDrawMode == 5)
    {
        float edge = min(min(barycentric.x, barycentric.y), barycentric.z);
        float thickness = 0.001;        
        if (edge < thickness)
            fragColor = vec4(0.75, 0.75, 0.75, 1.0);
        else
            discard;
    }
    else
    {        
        fragColor = color;
    }
}


