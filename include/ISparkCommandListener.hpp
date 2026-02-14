#ifndef __SPARK_UI_ISPARKCOMMANDLISTENER_HPP_INCLUDED__
#define __SPARK_UI_ISPARKCOMMANDLISTENER_HPP_INCLUDED__

#include "ui/Command.hpp"

namespace spark::ui {
    /**
    *
    */
    class ISparkCommandListener
    {
    public:
        virtual void executeCommand(spark::ui::Command::E_COMMAND_TYPE cmd, spark::ui::AbstractCanvas* canvas) = 0;
    };
}
#endif