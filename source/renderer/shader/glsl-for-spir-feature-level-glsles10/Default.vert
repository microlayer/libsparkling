#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in mat4 uModelViewProjectionMatrix;
layout(location = 4) out vec4 fragColor;

void main() 
{
    fragColor = aColor;
    gl_Position = uModelViewProjectionMatrix * vec4(aPosition, 1.0);    
}