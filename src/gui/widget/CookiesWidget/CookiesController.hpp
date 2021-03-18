#pragma once

#include <boost/format.hpp>
#include <memory>

#include "domain/RequestData.hpp"
#include "domain/BeforeRequestPipeline.hpp"
#include "gui/widget/CookiesWidget/ICookiesView.hpp"

namespace getit::gui::widget
{
    class CookiesController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit CookiesController(std::shared_ptr<ICookiesView> view);
            ~CookiesController() override = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<ICookiesView> view;

            const std::string cookieHeaderName = "Set-Cookie";
            const std::string cookieHeaderTemplate = "%1%=%2%";
    };
}