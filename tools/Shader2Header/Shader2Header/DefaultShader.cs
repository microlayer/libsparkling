namespace Shader2Header
{
    /// <summary>
    /// 
    /// </summary>
    internal class DefaultShader : IShaderInfo
    {
        /// <summary>
        /// 
        /// </summary>
        public string RootFolder
        {
            get;
            set;
        }

        /// <summary>
        /// 
        /// </summary>
        public string Version
        {
            get;
            set;
        }

        /// <summary>
        /// 
        /// </summary>
        public string ClassName
        {
            get;
            set;
        }

        /// <summary>
        /// 
        /// </summary>
        public string VertexName
        {
            get;
            set;
        }

        /// <summary>
        /// 
        /// </summary>
        public string FragmentName
        {
            get;
            set;
        }

        /// <summary>
        /// 
        /// </summary>
        public string Guard { get { return Version.Replace('-', '_').ToUpper(); } }

        /// <summary>
        /// 
        /// </summary>
        public string Namespace { get { return Version.Replace('-', '_'); } }
    }
}
