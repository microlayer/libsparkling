#version 300 es
precision mediump float;

// Varying
in vec4 color;
in vec3 vertexNormal;
in vec2 textureCoord;
in vec3 barycentric;
in vec3 fragPosition;

// Input
uniform sampler2D uTexture0;
uniform int uDrawMode;
uniform vec3 uFontColor;

// Light
uniform int uDirectionalLightCount;
uniform vec3 uDirectionalLightDirection[4];
uniform vec3 uDirectionalLightColor[4];
uniform float uDirectionalLightIntensity[4];

uniform int uPointLightCount;
uniform vec3 uPointLightPosition[4];
uniform vec3 uPointLightColor[4];
uniform float uPointLightIntensity[4];
uniform float uPointLightRange[4];

// PBR
uniform vec3 uAlbedo;
uniform float uRoughness;
uniform float uMetallic;

// Out
out vec4 fragColor;

#define MAX_LIGHTS 16

//--------------------------------------------------------------------------------------
// uDrawMode (uniform) sets the draw mode for this draw call.
//--------------------------------------------------------------------------------------
const int DRAW_TEXTURE     = 1; // DrawMode = 1: Used to draw texture
const int DRAW_FONT        = 2; // DrawMode = 2: Used to draw glyphs
const int DRAW_NORMALS     = 3; // DrawMode = 3: Used to draw Normal Vector Debug Visualization for mesh
const int DRAW_BARYCENTRIC = 4; // DrawMode = 4: Used to draw mesh with each triangle filled using its barycenter RGB color
const int DRAW_WIREFRAME   = 5; // DrawMode = 5: Used to draw mesh as wireframe
const int DRAW_DIFFUSE     = 6; // DrawMode = 6: Used to draw Diffuse Lighting (Lambert)
const int DRAW_PBR         = 7; // DrawMode = 7: Used to draw PBR Lighting

void main()
{
    if(uDrawMode == DRAW_TEXTURE)
    {
        fragColor = texture(uTexture0, textureCoord);
    }
    else if(uDrawMode == DRAW_FONT)
    {
        float alpha = texture(uTexture0, textureCoord.xy).x;
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
    else if(uDrawMode == DRAW_DIFFUSE)
    {       
        vec3 result = vec3(0.0);
        
        // Add Directional Lights
        for (int i = 0; i < MAX_LIGHTS; ++i)
        {
            if (i >= uDirectionalLightCount) { break;}

            vec3 N = normalize(vertexNormal);
            vec3 L = normalize(-uDirectionalLightDirection[i]);

            float NdotL = max(dot(N, L), 0.0);

            vec3 diffuse = uAlbedo * uDirectionalLightColor[i] * uDirectionalLightIntensity[i] * NdotL;

            result += diffuse;
        }

        // Add Point Lights
        for (int i = 0; i < MAX_LIGHTS; ++i)
        {
            if (i >= uPointLightCount) { break;}
            
            vec3 N = normalize(vertexNormal);
            vec3 lightDir = uPointLightPosition[i] - fragPosition;
                        
            float dist = length(lightDir);
            lightDir = normalize(lightDir);
            float NdotL = max(dot(N, lightDir), 0.0);
            float attenuation = 0.8 / (dist * dist);
            
            vec3 diffuse =
                uAlbedo *
                uPointLightColor[i] *
                uPointLightIntensity[i] *
                NdotL *
                attenuation;

            result += diffuse;
        }
        
        fragColor = vec4(result, 1.0);
    }
    else if(uDrawMode == DRAW_PBR)
    {
    }
    else
    {        
        fragColor = color;
    }
}


