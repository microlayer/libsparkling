#version 130

// Input
in vec3 aVertexPosition;
in vec3 aVertexNormal;
in vec4 aVertexColor;
in vec2 aTextureCoord;
in vec3 aBarycentric;

uniform mat4 uModelViewProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uModelMatrix;
uniform mat3 uNormalMatrix;

// Varying
out vec4 color;
out vec3 vertexNormal;
out vec2 textureCoord;
out vec3 barycentric;

out vec3 fragPosition;

const float POINT_SIZE = 3.0;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{	
    color = aVertexColor;       
    vertexNormal = normalize(uNormalMatrix * aVertexNormal);
    textureCoord = aTextureCoord;    
    barycentric = aBarycentric;
         
    vec4 worldPos = uModelMatrix * vec4(aVertexPosition, 1.0);
    fragPosition = worldPos.xyz;
    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
    gl_PointSize = POINT_SIZE;
}

