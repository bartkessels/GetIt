#pragma once

#include <list>
#include <string>
#include <trompeloeil.hpp>
#include <utility>

#include "gui/widget/HeadersWidget/IHeadersView.hpp"

class HeadersViewMock: public getit::gui::widget::IHeadersView
{
    public:
        ~HeadersViewMock() = default;

        MAKE_MOCK0(getHeaders, (std::list<std::pair<std::string, std::string>>()), override);
        MAKE_MOCK1(setHeaders, void(std::list<std::pair<std::string, std::string>>), override);
};