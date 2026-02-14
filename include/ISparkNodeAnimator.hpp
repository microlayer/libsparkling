#ifndef __SPARK_ANIMATOR_ISPARKNODEANIMATOR_HPP_INCLUDED__
#define __SPARK_ANIMATOR_ISPARKNODEANIMATOR_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark {
    namespace scene {
        class ISparkSceneNode;
    }
}

namespace spark::animator {
    /**
    *
    */
    class ISparkNodeAnimator : public virtual spark::SparkRefCount
    {
    public:
        virtual void animate(spark::scene::ISparkSceneNode* node) = 0;
    };
}
#endif