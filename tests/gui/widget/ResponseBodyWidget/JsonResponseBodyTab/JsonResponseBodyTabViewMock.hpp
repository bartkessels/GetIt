#pragma once

#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/ResponseBodyWidget/JsonResponseBodyTab/IJsonResponseBodyTabView.hpp"

class JsonResponseBodyTabViewMock: public getit::gui::widget::ResponseBodyWidget::IJsonResponseBodyTabView
{
    public:
        ~JsonResponseBodyTabViewMock() = default;

        MAKE_MOCK1(setBody, void(std::string), override);
};