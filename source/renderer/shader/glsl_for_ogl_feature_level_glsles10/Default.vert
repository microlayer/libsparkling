#version 130

// Input
in vec3 aVertexPosition;
in vec3 aVertexNormal;
in vec4 aVertexColor;
in vec2 aTextureCoord;
uniform vec3 uLightDirection;
uniform mat4 uModelViewProjectionMatrix;

// Varying
out vec4 color;
out vec3 vertexNormal;
out vec2 textureCoord;
out vec3 lightDirection;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{	
    color = aVertexColor;
    vertexNormal = aVertexNormal;
    textureCoord = aTextureCoord;
    lightDirection = uLightDirection;
    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
}

