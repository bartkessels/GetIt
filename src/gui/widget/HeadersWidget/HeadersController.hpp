#pragma once

#include <map>

#include "gui/widget/HeadersWidget/HeadersView.hpp"
#include "gui/BeforeWidgetController.hpp"

namespace getit::gui::widget
{
    class HeadersController: public BeforeWidgetController
    {
        public:
            ~HeadersController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data);
    };
}