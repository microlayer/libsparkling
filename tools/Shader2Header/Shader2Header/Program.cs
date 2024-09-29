// See https://aka.ms/new-console-template for more information
using IniParser;
using Shader2Header;

Console.WriteLine("Start");

var parser = new FileIniDataParser();
//IniData data = parser.ReadFile("Shader2Header.ini");

var defaultShader = new DefaultShader
{
    RootFolder = @"..\..\..\..\..\..\source\renderer\shader",
    Version = "glsl-for-ogl-feature-level-glsles10",
    ClassName = "DefaultShader",
    VertexName = "Default.vert",
    FragmentName = "Default.frag"
};

var converter = new ConverterCommand(defaultShader);
converter.Execute();