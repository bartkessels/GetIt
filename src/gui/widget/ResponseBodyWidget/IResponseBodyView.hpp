#pragma once

#include <QWidget>
#include <string>

namespace getit::gui::widget
{
    struct IResponseBodyView
    {
        public:
            ~IResponseBodyView() = default;

            virtual void addResponseBodyTab(QWidget* tab, std::string name) = 0;
    };
}