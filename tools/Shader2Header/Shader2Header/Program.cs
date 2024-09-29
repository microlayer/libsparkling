// See https://aka.ms/new-console-template for more information
using IniParser;
using Shader2Header;

Console.WriteLine("Start");

var parser = new FileIniDataParser();
//IniData data = parser.ReadFile("Shader2Header.ini");

var defaultShader1 = new DefaultShader
{
    RootFolder = @"..\..\..\..\..\..\source\renderer\shader",
    Version = "glsl_for_ogl_feature_level_glsles10",
    ClassName = "DefaultShader",
    VertexName = "Default.vert",
    FragmentName = "Default.frag"
};

var defaultShader2 = new DefaultShader
{
    RootFolder = @"..\..\..\..\..\..\source\renderer\shader",
    Version = "glsl_for_gles2_feature_level_glsles10",
    ClassName = "DefaultShader",
    VertexName = "Default.vert",
    FragmentName = "Default.frag"
};

var converter1 = new ConverterCommand(defaultShader1);
converter1.Execute();

var converter2 = new ConverterCommand(defaultShader2);
converter2.Execute();

Console.WriteLine("Completed successful");