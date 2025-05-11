#ifndef __SPARK_GAME_LINELAYER_HPP_INCLUDED__
#define __SPARK_GAME_LINELAYER_HPP_INCLUDED__

#include "AbstractLayer.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        class LineLayer : public spark::game::AbstractLayer
        {
        public:
            LineLayer();
            ~LineLayer();

        public: // AbstractLayer
            void paint(spark::renderer::ISparkRenderer* renderer);
        };
    }
}
#endif