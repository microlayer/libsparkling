#ifndef __SPARK_ANIMATOR_NODEROTATIONANIMATOR_HPP_INCLUDED__
#define __SPARK_ANIMATOR_NODEROTATIONANIMATOR_HPP_INCLUDED__

#include "ISparkNodeAnimator.hpp"
#include "timer/Timer.hpp"

namespace spark::animator {
    /**
    *
    */
    class NodeRotationAnimator : public spark::animator::ISparkNodeAnimator
    {
    private:
        NodeRotationAnimator(spark::math::Vector3f degreePerSecond);
    public:
        virtual ~NodeRotationAnimator(void);

    public:
        void animate(spark::scene::ISparkSceneNode* node);

    public:
        static ISparkNodeAnimator* create(spark::math::Vector3f degreePerSecond);

    private:
        spark::timer::Timer m_timer;
        uint32_t m_startTime;
        spark::math::Vector3f m_degreePerSecond;
        spark::math::Vector3f m_radPerSecond;
        spark::math::Vector3f m_radPerMillisecond;
        spark::math::Vector3f m_rotation;
    };
}
#endif