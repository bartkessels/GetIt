#pragma once

#include <memory>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "gui/widget/HeadersWidget/IHeadersView.hpp"

namespace getit::gui::widget
{
    class HeadersController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit HeadersController(std::shared_ptr<IHeadersView> view);
            ~HeadersController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<IHeadersView> view;
    };
}