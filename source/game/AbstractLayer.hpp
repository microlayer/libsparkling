#ifndef __SPARK_GAME_ABSTRACTLAYER_HPP_INCLUDED__
#define __SPARK_GAME_ABSTRACTLAYER_HPP_INCLUDED__

#include "ISparkRenderer.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        class AbstractLayer : public virtual spark::SparkRefCount
        {
        public:
            /**
            *
            */
            AbstractLayer() :
                m_x(0),
                m_y(0),
                m_zAxisRotation(0)
            {

            }

            /**
            *
            */
            virtual ~AbstractLayer(void)
            {
            }

            /**
            *
            */
            virtual void setPosition(int16_t x, int16_t y)
            {

            }

            /**
            *
            */
            virtual void setRotation(real32 zAxisRotation)
            {

            }

            /**
            *
            */
            virtual real32 getRotation()
            {

                return m_zAxisRotation;
            }

            /**
            *
            */
            virtual void move(int16_t dx, int16_t dy)
            {

            }

            /**
            *
            */
            virtual void paint(spark::renderer::ISparkRenderer* renderer) = 0;

        protected:
            int16_t m_x;
            int16_t m_y;
            real32 m_zAxisRotation;
        };

    } // end namespace game
} // end namespace spark
#endif