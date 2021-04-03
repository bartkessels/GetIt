#pragma once

#include <memory>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/JsonResponseBodyTab/IJsonResponseBodyTabView.hpp"

namespace getit::gui::widget::ResponseBodyWidget
{
    class JsonResponseBodyTabController: public getit::domain::AfterRequestPipeline
    {
        public:
            explicit JsonResponseBodyTabController(std::shared_ptr<IJsonResponseBodyTabView> view);
            ~JsonResponseBodyTabController() override = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response) override;

        private:
            std::shared_ptr<IJsonResponseBodyTabView> view;
    };
}