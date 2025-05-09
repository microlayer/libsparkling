//------------------------------------------------------------------------------
// <auto-generated>
//	This code was generated by a tool
//	Changes will be lost if code is regenerated
// </auto-generated>
//------------------------------------------------------------------------------
#ifndef __SPARK_RENDERER_SHADER_GLSL_FOR_GLES2_FEATURE_LEVEL_GLSLES10_DEFAULTSHADER_HPP_INCLUDED__
#define __SPARK_RENDERER_SHADER_GLSL_FOR_GLES2_FEATURE_LEVEL_GLSLES10_DEFAULTSHADER_HPP_INCLUDED__

namespace spark {
	namespace renderer {
		namespace shader {
			namespace glsl_for_gles2_feature_level_glsles10 {
				/// <summary>
				///
				/// <summary>
				class DefaultShader
				{
				public:
					/// <summary>
					///
					/// <summary>
					DefaultShader(void)
					{
					}

					/// <summary>
					///
					/// <summary>
					virtual ~DefaultShader(void)
					{
					}

				public:
					/// <summary>
					///
					/// <summary>
					const char* GetVertexShader() const
					{
						const char* vertexShaderStr =
							"#version 100\n"
							"precision mediump float;\n"
							"\n"
							"// Input\n"
							"attribute vec3 aVertexPosition;\n"
							"attribute vec3 aVertexNormal;\n"
							"attribute vec4 aVertexColor;\n"
							"attribute vec2 aTextureCoord;\n"
							"uniform mat4 uModelViewProjectionMatrix;\n"
							"\n"
							"// Varying\n"
							"varying vec4 color;\n"
							"varying vec2 textureCoord;\n"
							"\n"
							"//--------------------------------------------------------------------------------------\n"
							"//\n"
							"//--------------------------------------------------------------------------------------\n"
							"void main()\n"
							"{\n"
							"    color = aVertexColor;\n"
							"    textureCoord = aTextureCoord;\n"
							"    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);\n"
							"}\n"
							"\n"
							"\n"
							;
						return vertexShaderStr;
					}

					/// <summary>
					///
					/// <summary>
					const char* GetFragmentShader() const
					{
						const char* fragmentShaderStr =
							"#version 100\n"
							"precision mediump float;\n"
							"\n"
							"// Varying\n"
							"varying vec4 color;\n"
							"varying vec2 textureCoord;\n"
							"\n"
							"// Input\n"
							"uniform sampler2D uTexture0;\n"
							"uniform int uDrawMode;\n"
							"uniform vec3 uFontColor;\n"
							"\n"
							"//--------------------------------------------------------------------------------------\n"
							"// DrawMode = 1: Used to draw texture\n"
							"// DrawMode = 2: Used to draw glyphs\n"
							"//--------------------------------------------------------------------------------------\n"
							"void main()\n"
							"{\n"
							"    if(uDrawMode == 1)\n"
							"    {\n"
							"        gl_FragColor = texture2D(uTexture0, textureCoord);\n"
							"    }\n"
							"    else if(uDrawMode == 2)\n"
							"    {\n"
							"        float alpha = texture2D(uTexture0, textureCoord.xy).x;\n"
							"        gl_FragColor = vec4(uFontColor, alpha);\n"
							"    }\n"
							"    else\n"
							"    {\n"
							"        gl_FragColor = color;\n"
							"    }\n"
							"}\n"
							"\n"
							"\n"
							"\n"
							;
						return fragmentShaderStr;
					}

				};
			}
		}
	}
}
#endif
