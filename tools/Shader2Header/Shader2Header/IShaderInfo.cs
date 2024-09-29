namespace Shader2Header
{
    /// <summary>
    /// 
    /// </summary>
    internal interface IShaderInfo
    {
        string RootFolder { get; }
        string Version { get; set; }
        string ClassName { get; }
        string VertexName { get; }
        string FragmentName { get; }
        string Guard { get; }
        string Namespace { get; }
    }
}
