#version 130

// Input
attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec4 aVertexColor;
attribute vec2 aTextureCoord;
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

