#pragma once

#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/BodyWidget/RawBodyTab/IRawBodyTabView.hpp"

class RawBodyTabViewMock: public getit::gui::widget::BodyWidget::IRawBodyTabView
{
    public:
        ~RawBodyTabViewMock() = default;

        MAKE_MOCK0(getContentType, std::string(), override);
        MAKE_MOCK0(getBody, std::string(), override);

        MAKE_MOCK1(setContentType, void(std::string), override);
        MAKE_MOCK1(setBody, void(std::string), override);
};