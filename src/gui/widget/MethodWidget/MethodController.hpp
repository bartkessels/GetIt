#pragma once

#include <memory>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "gui/widget/MethodWidget/IMethodView.hpp"

namespace getit::gui::widget
{
    class MethodController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit MethodController(std::shared_ptr<IMethodView> view);
            ~MethodController() override = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<IMethodView> view;
    };
}