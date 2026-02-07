#version 100
precision mediump float;

// Input
attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec4 aVertexColor;
attribute vec2 aTextureCoord;
attribute vec3 aBarycentric;
uniform vec3 uLightDirection;
uniform mat4 uModelViewProjectionMatrix;

// Varying
varying vec4 color;
varying vec3 vertexNormal;
varying vec2 textureCoord;
varying vec3 lightDirection;
varying vec3 barycentric;

const float POINT_SIZE = 3.0;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{    
    color = aVertexColor;
    vertexNormal = aVertexNormal;
    textureCoord = aTextureCoord;
    lightDirection = uLightDirection;
    barycentric = aBarycentric;
        
    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
    gl_PointSize = POINT_SIZE;
}

