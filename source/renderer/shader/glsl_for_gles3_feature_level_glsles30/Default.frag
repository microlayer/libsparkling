#version 300 es
precision mediump float;

// Varying
in vec4 color;
in vec3 vertexNormal;
in vec2 textureCoord;
in vec3 barycentric;
in vec3 fragPosition;
in vec4 fragShadowCoord;

// Mode
uniform int uDrawMode;

// Font
uniform vec3 uFontColor;

// Light
uniform int uDirectionalLightCount;
uniform vec3 uDirectionalLightDirection[4];
uniform vec3 uDirectionalLightColor[4];
uniform float uDirectionalLightIntensity[4];

uniform int uSpotLightCount;
uniform vec3 uSpotLightPosition[4];
uniform vec3 uSpotLightDirection[4];
uniform vec3 uSpotLightColor[4];
uniform float uSpotLightRange[4];
uniform float uSpotLightAngle[4];
uniform float uSpotLightIntensity[4];

uniform int uPointLightCount;
uniform vec3 uPointLightPosition[4];
uniform vec3 uPointLightColor[4];
uniform float uPointLightIntensity[4];
uniform float uPointLightRange[4];

// Diffuse
uniform vec3 uAlbedo; // default: (1,1,1)

// PBR
uniform float uRoughness;
uniform float uMetallic;
uniform float uAo;

// Texture
uniform sampler2D uDefaultTexture;  // default: unit0
uniform sampler2D uAlbedoMap;       // default: unit1
uniform sampler2D uNormalMap;       // default: unit2
uniform sampler2D uRoughnessMap;    // default: unit3
uniform sampler2D uMetallicMap;     // default: unit4
uniform sampler2D uShadowMap;       // default: unit7

uniform bool uHasAlbedoTexture;
uniform bool uHasShadowMap; // default: false

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
const int DRAW_UNLIT       = 6; // DrawMode = 6: Used to draw texture without Lighting
const int DRAW_DIFFUSE     = 7; // DrawMode = 7: Used to draw Diffuse Lighting (Lambert)
const int DRAW_PBR         = 8; // DrawMode = 8: Used to draw PBR Lighting
const int DRAW_SHADOWMAP   = 9; // DrawMode = 9: Used to draw Shadow Map

float calculateShadow()
{
    vec3 projCoords = fragShadowCoord.xyz / fragShadowCoord.w;
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(uShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float bias = 0.005;

    return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

void main()
{
    if(uDrawMode == DRAW_TEXTURE)
    {
        vec4 tex = texture(uDefaultTexture, textureCoord);
        fragColor = vec4(tex.rgb * uAlbedo, tex.a);
    }
    else if(uDrawMode == DRAW_FONT)
    {
        float alpha = texture(uDefaultTexture, textureCoord.xy).x;
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
    else if(uDrawMode == DRAW_UNLIT)
    {
        vec4 tex = texture(uAlbedoMap, textureCoord);
        fragColor = vec4(tex.rgb * uAlbedo, tex.a);
    }
    else if(uDrawMode == DRAW_DIFFUSE)
    {       
        float shadow = 0.0;

        if (uHasShadowMap)
        {
            shadow = calculateShadow();
        }
        
        vec3 result = vec3(0.0);
         
        vec3 albedo = uAlbedo;
        if (uHasAlbedoTexture)
        {
            albedo *= texture(uAlbedoMap, textureCoord).rgb;           
        }
        
        // Add Directional Lights
        for (int i = 0; i < uDirectionalLightCount; ++i)
        {
            vec3 N = normalize(vertexNormal);
            vec3 L = normalize(-uDirectionalLightDirection[i]);

            float NdotL = max(dot(N, L), 0.0);

            vec3 diffuse = 
                albedo * 
                uDirectionalLightColor[i] * 
                uDirectionalLightIntensity[i] * 
                NdotL * (1.0 - shadow);

            result += diffuse;
        }

        // Add Spot Lights
        for (int i = 0; i < uSpotLightCount; ++i)
        {
            vec3 N = normalize(vertexNormal);

            vec3 lightDir = uSpotLightPosition[i] - fragPosition;

            float dist = length(lightDir);
            lightDir = normalize(lightDir);

            float NdotL = max(dot(N, lightDir), 0.0);

            // Distance attenuation
            float rangeFactor = 1.0 - smoothstep(0.0, uSpotLightRange[i], dist);
            float attenuation = 0.8 / (dist * dist) * rangeFactor;

            // Spot cone
            vec3 spotDirection = normalize(uSpotLightDirection[i]);

            float theta = dot(-lightDir, spotDirection);
            float cutoff = cos(uSpotLightAngle[i]);

            float spotFactor = theta >= cutoff ? 1.0 : 0.0;

            vec3 diffuse =
                albedo *
                uSpotLightColor[i] *
                uSpotLightIntensity[i] *
                NdotL *
                attenuation *
                spotFactor *
                (1.0 - shadow);

            result += diffuse;
        }

        // Add Point Lights
        for (int i = 0; i < uPointLightCount; ++i)
        {                        
            vec3 N = normalize(vertexNormal);
            vec3 lightDir = uPointLightPosition[i] - fragPosition;
                        
            float dist = length(lightDir);
            lightDir = normalize(lightDir);
            float NdotL = max(dot(N, lightDir), 0.0);
            float attenuation = 0.8 / (dist * dist);
            
            vec3 diffuse =
                albedo *
                uPointLightColor[i] *
                uPointLightIntensity[i] *
                NdotL *
                attenuation *
                (1.0 - shadow);

            result += diffuse;
        }
        
        fragColor = vec4(result, 1.0);
    }
    else if(uDrawMode == DRAW_PBR)
    {
    }
    else if(uDrawMode == DRAW_SHADOWMAP)
    {
        float depth = texture(uShadowMap, textureCoord).r;
        fragColor = vec4(depth, depth, depth, 1.0);
    }
    else
    {        
        fragColor = color;
    }
}

