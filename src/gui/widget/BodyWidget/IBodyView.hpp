#pragma once

#include <QWidget>
#include <string>

namespace getit::gui::widget
{
    struct IBodyView
    {
        public:
            ~IBodyView() = default;

            virtual void addBodyTab(QWidget* tab, std::string name) = 0;
            virtual int getSelectedTabIndex() = 0;
    };
}