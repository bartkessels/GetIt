#pragma once

#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/MethodWidget/IMethodView.hpp"

class MethodViewMock: public getit::gui::widget::IMethodView
{
    public:
        ~MethodViewMock() = default;

        MAKE_MOCK0(getMethod, std::string(), override);
        MAKE_MOCK1(setMethod, void(std::string), override);
};