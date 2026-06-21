#version 100
precision mediump float;

// Input
attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec4 aVertexColor;
attribute vec2 aTextureCoord;
attribute vec3 aBarycentric;

uniform mat4 uModelViewProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uModelMatrix;
uniform mat3 uNormalMatrix;

// Varying
varying vec4 color;
varying vec3 vertexNormal;
varying vec2 textureCoord;
varying vec3 barycentric;

varying vec3 fragPosition;

const float POINT_SIZE = 3.0;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{    
    color = aVertexColor;
    vertexNormal = normalize(uNormalMatrix * aVertexNormal);;
    textureCoord = aTextureCoord;
    barycentric = aBarycentric;
        
    vec4 worldPos = uModelMatrix * vec4(aVertexPosition, 1.0);
    fragPosition = worldPos.xyz;
    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
    gl_PointSize = POINT_SIZE;
}

