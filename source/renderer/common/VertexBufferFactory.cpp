#include "VertexBufferFactory.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        VertexBufferFactory::VertexBufferFactory(spark::log::ISparkLogger* logger)
        {

        }

        /**
        *
        */
        VertexBufferFactory::~VertexBufferFactory()
        {

        }

        /**
        *
        */
        spark::renderer::ISparkVertexBuffer* VertexBufferFactory::createOrUpdate(std::string id)
        {
            return NULL;
        }
    }
}
