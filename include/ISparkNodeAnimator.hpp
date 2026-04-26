#ifndef __SPARK_ANIMATOR_ISPARKNODEANIMATOR_HPP_INCLUDED__
#define __SPARK_ANIMATOR_ISPARKNODEANIMATOR_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark {
    namespace scene {
        namespace nodes {
            class ISparkSceneNode;
        }
    }
}

namespace spark::animator {
    /**
    *
    */
    class ISparkNodeAnimator : public virtual spark::SparkRefCount
    {
    public:
        virtual void animate(spark::scene::nodes::ISparkSceneNode* node) = 0;
    };
}
#endif