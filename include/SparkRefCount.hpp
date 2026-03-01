#ifndef __SPARK_SPARKREFCOUNT_HPP_INCLUDED__
#define __SPARK_SPARKREFCOUNT_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark {
    /**
    *
    */
    class SparkRefCount
    {
    public:
        /**
        *
        */
        SparkRefCount() : m_debugName(0), m_referenceCounter(1)
        {
        }

        /**
        *
        */
        virtual ~SparkRefCount()
        {
        }

        /**
        * @brief If reference count is 0, object will be deleted
        */
        bool release() const
        {
            --m_referenceCounter;
            if (m_referenceCounter == 0)
            {
                delete this;
                return true;
            }
            return false;
        }

        /**
        *
        */
        void addRef()
        {
            m_referenceCounter++;
        }

    protected:
        const c8_t* m_debugName;
        mutable int32_t m_referenceCounter;
    };
} // end namespace spark
#endif