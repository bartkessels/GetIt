#pragma once

#include <memory>
#include <string>
#include <QWidget>
#include <vector>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/IResponseBodyView.hpp"

namespace getit::gui::widget
{
    class ResponseBodyController: public getit::domain::AfterRequestPipeline
    {
        public:
            explicit ResponseBodyController(std::shared_ptr<IResponseBodyView> view);
            ~ResponseBodyController() override = default;

            void registerTab(std::shared_ptr<getit::domain::AfterRequestPipeline> tab, std::shared_ptr<QWidget> body, std::string name);
            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response) override;

        private:
            std::shared_ptr<IResponseBodyView> view;
            std::vector<std::shared_ptr<getit::domain::AfterRequestPipeline>> tabControllers;
    };
}