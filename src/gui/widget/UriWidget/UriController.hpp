#pragma once

#include <memory>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "gui/widget/UriWidget/IUriView.hpp"

namespace getit::gui::widget
{
    class UriController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit UriController(std::shared_ptr<IUriView> view);
            ~UriController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<IUriView> view;
    };
}
