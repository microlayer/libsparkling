#include "NodeRotationAnimator.hpp"

namespace spark {
    namespace animator {

        /**
        *
        */
        NodeRotationAnimator::NodeRotationAnimator(spark::math::Vector3f degreePerSecond) :
            m_startTime(0),
            m_rotation(0, 0, 0),
            m_degreePerSecond(degreePerSecond)
        {
            const real32 PI = 3.14159265f;

            m_radPerSecond.m_x = m_degreePerSecond.m_x * PI / 180.0f;
            m_radPerSecond.m_y = m_degreePerSecond.m_y * PI / 180.0f;
            m_radPerSecond.m_z = m_degreePerSecond.m_z * PI / 180.0f;

            m_radPerMillisecond.m_x = m_radPerSecond.m_x / 1000.0f;
            m_radPerMillisecond.m_y = m_radPerSecond.m_y / 1000.0f;
            m_radPerMillisecond.m_z = m_radPerSecond.m_z / 1000.0f;
        }

        /**
        *
        */
        NodeRotationAnimator::~NodeRotationAnimator()
        {
        }

        /**
        *
        */
        void NodeRotationAnimator::animate(/*spark::scene::ISparkSceneNode* node*/)
        {
            const uint32_t timestamp = m_timer.getTimestamp();
            const uint32_t diffTime = timestamp - m_startTime;

            if (diffTime != 0)
            {
                real32 incPerFrameX = m_radPerMillisecond.m_x * diffTime;
                real32 incPerFrameY = m_radPerMillisecond.m_y * diffTime;
                real32 incPerFrameZ = m_radPerMillisecond.m_z * diffTime;

                m_rotation.m_x = fmod(m_rotation.m_x + incPerFrameX, 6.2832f);
                m_rotation.m_y = fmod(m_rotation.m_y + incPerFrameY, 6.2832f);
                m_rotation.m_z = fmod(m_rotation.m_z + incPerFrameZ, 6.2832f);

                //node->setRotation(m_rotation);

                m_startTime = timestamp;

                //spark::log::LogManager::GetLogger()->Info("diffTime: %i - FPS: %f - Inc X-axis: %f - Inc Y-axis: %f - Inc Z-axis: %f", diffTime, 1/(diffTime/1000.0f), valX, valY , valZ);
            }
        }

    } // end namespace animator
} // end namespace spark