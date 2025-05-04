#version 130

// Input
in vec3 aVertexPosition;
in vec3 aVertexNormal;
in vec4 aVertexColor;
in vec2 aTextureCoord;
uniform mat4 uModelViewProjectionMatrix;

// Varying
out vec4 color;
out vec2 textureCoord;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{	
    color = aVertexColor;
    textureCoord = aTextureCoord;
    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
}

