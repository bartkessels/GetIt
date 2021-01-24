#pragma once

#include "gui/widget/UriWidget/UriView.hpp"
#include "gui/BeforeWidgetController.hpp"

namespace getit::gui::widget
{
    class UriController: public BeforeWidgetController
    {
        public:
            ~UriController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data);
    };
}