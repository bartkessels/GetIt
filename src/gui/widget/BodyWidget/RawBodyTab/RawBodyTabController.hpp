#pragma once

#include <memory>
#include <string>

#include "domain/body/RawRequestBody.hpp"
#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "gui/widget/BodyWidget/RawBodyTab/IRawBodyTabView.hpp"

namespace getit::gui::widget::BodyWidget
{
    class RawBodyTabController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit RawBodyTabController(std::shared_ptr<IRawBodyTabView> view);
            ~RawBodyTabController() override = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<IRawBodyTabView> view;
    };
}