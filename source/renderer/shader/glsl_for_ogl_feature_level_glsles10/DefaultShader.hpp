//------------------------------------------------------------------------------
// <auto-generated>
//	This code was generated by a tool
//	Changes will be lost if code is regenerated
// </auto-generated>
//------------------------------------------------------------------------------
#ifndef __SPARK_RENDERER_SHADER_GLSLFLES10DEFAULTSHADER_HPP_INCLUDED__
#define __SPARK_RENDERER_SHADER_GLSLFLES10DEFAULTSHADER_HPP_INCLUDED__

namespace spark {
	namespace renderer {
		namespace shader {
			namespace glslfles10 {
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
							"attribute vec3 aPosition;\n"
							"attribute vec3 aNormal;\n"
							"attribute vec4 aColor;\n"
							"attribute vec2 aTextureCoord;\n"
							"uniform mat4 uModelViewProjectionMatrix;\n"
							"\n"
							"varying vec4 Color;\n"
							"\n"
							"//--------------------------------------------------------------------------------------\n"
							"//\n"
							"//--------------------------------------------------------------------------------------\n"
							"void main()\n"
							"{	\n"
                            "   Color = aColor;\n"
							"	gl_Position = uModelViewProjectionMatrix * vec4(aPosition, 1.0);\n"                            
							"}\n"
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
							"varying vec4 Color;\n"
							"\n"
							"//--------------------------------------------------------------------------------------\n"
							"//\n"
							"//--------------------------------------------------------------------------------------\n"
							"void main()\n"
							"{\n"
							"	gl_FragColor = Color;\n"
							"}\n"
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