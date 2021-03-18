#pragma once

#include <memory>
#include <string>
#include <QWidget>
#include <vector>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "gui/widget/BodyWidget/IBodyView.hpp"

namespace getit::gui::widget
{
    class BodyController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit BodyController(std::shared_ptr<IBodyView> view);
            ~BodyController() override = default;

            void registerTab(std::shared_ptr<getit::domain::BeforeRequestPipeline> tab, std::shared_ptr<QWidget> body, std::string name);

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<IBodyView> view;

            std::vector<std::shared_ptr<getit::domain::BeforeRequestPipeline>> tabControllers;
    };
}
