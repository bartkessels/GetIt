#pragma once

#include <ctime>
#include <map>
#include <memory>
#include <string>

#include "domain/body/FormdataRequestBody.hpp"
#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "gui/widget/BodyWidget/FormdataBodyTab/IFormdataBodyTabView.hpp"

namespace getit::gui::widget::BodyWidget
{
    class FormdataBodyTabController: public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit FormdataBodyTabController(std::shared_ptr<IFormdataBodyTabView> view);
            ~FormdataBodyTabController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            std::shared_ptr<IFormdataBodyTabView> view;
    };
}