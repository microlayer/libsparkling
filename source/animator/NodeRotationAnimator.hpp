#ifndef __SPARK_ANIMATOR_NODEROTATIONANIMATOR_HPP_INCLUDED__
#define __SPARK_ANIMATOR_NODEROTATIONANIMATOR_HPP_INCLUDED__

#include "ISparkNodeAnimator.hpp"
#include "math/Vector3.hpp"
#include <math.h>
#include "log/LogManager.hpp"
#include "timer/Timer.hpp"

namespace spark {
    namespace animator {

        /**
        *
        */
        class NodeRotationAnimator : public spark::animator::ISparkNodeAnimator
        {
        public:
            NodeRotationAnimator(spark::math::Vector3f degreePerSecond);
            virtual ~NodeRotationAnimator(void);

        public:
            void animate(/*spark::scene::ISparkSceneNode* node*/);

        private:
            spark::timer::Timer m_timer;
            uint32_t m_startTime;
            spark::math::Vector3f m_degreePerSecond;
            spark::math::Vector3f m_radPerSecond;
            spark::math::Vector3f m_radPerMillisecond;
            spark::math::Vector3f m_rotation;
        };
    } // end namespace animator
} // end namespace spark
#endif