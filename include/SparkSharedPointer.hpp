#ifndef __SPARK_SPARKSHAREDPOINTER_HPP_INCLUDED__
#define __SPARK_SPARKSHAREDPOINTER_HPP_INCLUDED__

#include <type_traits>

namespace spark {
    /**
    *
    */
    template <class T>
    class SparkSharedPointer
    {
    public:
        /**
        *
        */
        /*explicit*/ SparkSharedPointer(T* ptr = NULL) : m_ptr(ptr)
        {
            static_assert(std::is_base_of<SparkRefCount, T>::value, "Type parameter of this class must derive from SparkRefCount");
        }

        /**
        *
        */
        SparkSharedPointer(const SparkSharedPointer& other)
        {
            std::cout << "copy constructor";
            m_ptr = other.m_ptr;
            ((SparkRefCount*)m_ptr)->addRef();
        }

        /**
        *
        */
        ~SparkSharedPointer()
        {
            if (m_ptr)
            {
                static_cast<SparkRefCount*>(m_ptr)->release();
            }
        }

        /**
        *
        */
        SparkSharedPointer& operator=(const SparkSharedPointer& other)
        {
            m_ptr = other.m_ptr;
            static_cast<SparkRefCount*>(m_ptr)->addRef();
            return *this;
        }

        /**
        *
        */
        T* get() const
        {
            return m_ptr;
        }

        /**
        * Overloaded dereference operator
        */
        T& operator*() const
        {
            return *m_ptr;
        }

        /**
        * Overloaded arrow operator
        */
        T* operator->() const
        {
            return m_ptr;
        }

    private:
        T* m_ptr;
    };

    /**
    * Creates a SparkSharedPointer
    */
    template<typename T, typename... Args>
    static spark::SparkSharedPointer<T> makeShared(Args&&... args)
    {
        return SparkSharedPointer<T>(new T(std::forward<Args>(args)...));
    }
}
#endif