#pragma once

#include <map>

#include "gui/widget/ResponseHeadersWidget/ResponseHeadersView.hpp"
#include "gui/AfterWidgetController.hpp"

namespace getit::gui::widget
{
    class ResponseHeadersController: public AfterWidgetController
    {
        public:
            ~ResponseHeadersController() override = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response) override;
    };
}