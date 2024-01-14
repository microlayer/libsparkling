#ifndef __SPARK_DEVICE_WINDOW_ISPARKWINDOW_HPP_INCLUDED__
#define __SPARK_DEVICE_WINDOW_ISPARKWINDOW_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "SparkRefCount.hpp"

namespace spark {
    namespace device {
        namespace window {

            class ISparkWindow : public spark::SparkRefCount
            {
            public:
                virtual void* getNativeWindow() = 0;
            };
        } // end namespace window
    } // end namespace device
} // end namespace spark
#endif