#pragma once

#include <boost/format.hpp>
#include <map>

#include "gui/widget/CookiesWidget/CookiesView.hpp"
#include "gui/BeforeWidgetController.hpp"

namespace getit::gui::widget
{
    class CookiesController: public BeforeWidgetController
    {
        public:
            ~CookiesController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data);

        private:
            const std::string cookieHeaderName = "Set-Cookie";
            const std::string cookieHeaderTemplate = "%1%=%2%";
    };
}