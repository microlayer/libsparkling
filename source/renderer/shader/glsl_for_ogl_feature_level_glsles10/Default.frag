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
//--------------------------------------------------------------------------------------
const int DRAW_TEXTURE     = 1; // DrawMode = 1: Used to draw texture
const int DRAW_FONT        = 2; // DrawMode = 2: Used to draw glyphs
const int DRAW_NORMALS     = 3; // DrawMode = 3: Used to draw Normal Vector Debug Visualization for mesh
const int DRAW_BARYCENTRIC = 4; // DrawMode = 4: Used to draw mesh with each triangle filled using its barycenter RGB color
const int DRAW_WIREFRAME   = 5; // DrawMode = 5: Used to draw mesh as wireframe

void main()
{
    if(uDrawMode == DRAW_TEXTURE)
    {
        fragColor = texture2D(uTexture0, textureCoord);
    }
    else if(uDrawMode == DRAW_FONT)
    {
        float alpha = texture2D(uTexture0, textureCoord.xy).x;
        fragColor = vec4(uFontColor, alpha);
    }
    else if(uDrawMode == DRAW_NORMALS)
    {
        vec3 n = normalize(vertexNormal.xyz);
        fragColor = vec4(n * 0.5 + 0.5, 1.0);
    }
    else if(uDrawMode == DRAW_BARYCENTRIC)
    {
        fragColor = vec4(barycentric, 1.0);
    }
    else if(uDrawMode == DRAW_WIREFRAME)
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


