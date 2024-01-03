#version 100
precision mediump float;

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec4 aColor;
attribute vec2 aTextureCoord;
uniform mat4 uModelViewProjectionMatrix;

varying vec4 Color;

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void main()
{	
    Color = aColor;
	gl_Position = uModelViewProjectionMatrix * vec4(aPosition, 1.0);    
}
