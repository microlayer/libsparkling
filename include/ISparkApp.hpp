#ifndef __SPARK_APPLICATION_ISPARKAPP_HPP_INCLUDED__
#define __SPARK_APPLICATION_ISPARKAPP_HPP_INCLUDED__

namespace spark {
    namespace app {
        /**
        *
        */
        class ISparkApp
        {
        public:
            virtual void onInit() = 0;
        };
    } // end namespace application
} // end namespace spark
#endif