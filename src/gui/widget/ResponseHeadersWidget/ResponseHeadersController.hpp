#pragma once

#include <memory>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/Response.hpp"
#include "gui/widget/ResponseHeadersWidget/IResponseHeadersView.hpp"

namespace getit::gui::widget
{
    class ResponseHeadersController: public getit::domain::AfterRequestPipeline
    {
        public:
            explicit ResponseHeadersController(std::shared_ptr<IResponseHeadersView> view);
            ~ResponseHeadersController() override = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response) override;

        private:
            std::shared_ptr<IResponseHeadersView> view;
    };
}