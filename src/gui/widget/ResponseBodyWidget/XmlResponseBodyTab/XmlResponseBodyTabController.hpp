#pragma once

#include <memory>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/IXmlResponseBodyTabView.hpp"

namespace getit::gui::widget::ResponseBodyWidget
{
    class XmlResponseBodyTabController: public getit::domain::AfterRequestPipeline
    {
        public:
            explicit XmlResponseBodyTabController(std::shared_ptr<IXmlResponseBodyTabView> view);
            ~XmlResponseBodyTabController() override = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response) override;

        private:
            std::shared_ptr<IXmlResponseBodyTabView> view;
    };
}