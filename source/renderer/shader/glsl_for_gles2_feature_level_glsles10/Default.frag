#version 100
precision mediump float;

// Varying
varying vec4 color;
varying vec3 vertexNormal;
varying vec2 textureCoord;
varying vec3 lightDirection;
varying vec3 barycentric;

// Input
uniform sampler2D uTexture0;
uniform int uDrawMode;
uniform vec3 uFontColor;

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
        gl_FragColor = texture2D(uTexture0, textureCoord);
    }
    else if(uDrawMode == DRAW_FONT)
    {
        float alpha = texture2D(uTexture0, textureCoord.xy).x;
        gl_FragColor = vec4(uFontColor, alpha);
    }
    else if(uDrawMode == DRAW_NORMALS)
    {
        vec3 n = normalize(vertexNormal.xyz);
        gl_FragColor = vec4(n * 0.5 + 0.5, 1.0);
    }
    else if(uDrawMode == DRAW_BARYCENTRIC)
    {
        gl_FragColor = vec4(barycentric, 1.0);
    }
    else if(uDrawMode == DRAW_WIREFRAME)
    {
        float edge = min(min(barycentric.x, barycentric.y), barycentric.z);
        float thickness = 0.001;        
        if (edge < thickness)
            gl_FragColor = vec4(0.75, 0.75, 0.75, 1.0);
        else
            discard;
    }
    else
    {        
        gl_FragColor = color;
    }
}


