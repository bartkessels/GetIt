#pragma once

#include <memory>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/IRawResponseBodyTabView.hpp"

namespace getit::gui::widget::ResponseBodyWidget
{
    class RawResponseBodyTabController: public getit::domain::AfterRequestPipeline
    {
        public:
            explicit RawResponseBodyTabController(std::shared_ptr<IRawResponseBodyTabView> view);
            ~RawResponseBodyTabController() override = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response) override;

        private:
            std::shared_ptr<IRawResponseBodyTabView> view;
    };
}