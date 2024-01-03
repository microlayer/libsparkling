#ifndef __SPARK_UI_COMMAND_HPP_INCLUDED__
#define __SPARK_UI_COMMAND_HPP_INCLUDED__

namespace spark {
    namespace ui {
        /**
        *
        */
        struct Command
        {
        public:
            enum E_COMMAND_TYPE
            {
                ECT_BACK,
                ECT_HOME,
                ECT_EXIT,
            };
        };
    } // end namespace ui
} // end namespace spark
#endif