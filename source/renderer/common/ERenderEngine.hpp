#ifndef __SPARK_RENDERER_ERENDERENGINE_HPP_INCLUDED__
#define __SPARK_RENDERER_ERENDERENGINE_HPP_INCLUDED__

namespace spark::renderer {
    /**
    *
    */
    enum E_RENDER_ENGINE
    {
        ERE_OGLFLES2 = 0,
        ERE_D3D11FL93,
        ERE_OGLES2,
        ERE_VULKAN13
    };
};
#endif