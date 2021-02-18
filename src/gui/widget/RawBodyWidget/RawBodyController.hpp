#pragma once

#include <string>

#include "gui/widget/RawBodyWidget/RawBodyView.hpp"
#include "gui/BeforeWidgetController.hpp"

namespace getit::gui::widget
{
    class RawBodyController: public BeforeWidgetController
    {
        public:
            ~RawBodyController() = default;
            
            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data);

        private:
            const std::string contentTypeHeader = "Content-Type";
    };
}
