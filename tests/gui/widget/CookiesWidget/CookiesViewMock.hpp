#pragma once

#include <list>
#include <memory>
#include <string>
#include <trompeloeil.hpp>
#include <utility>

#include "gui/widget/CookiesWidget/ICookiesView.hpp"

class CookiesViewMock: public getit::gui::widget::ICookiesView
{
    public:
        ~CookiesViewMock() = default;

        MAKE_MOCK0(getCookies, (std::list<std::pair<std::string, std::string>>()), override);
        MAKE_MOCK1(setCookies, void(std::list<std::pair<std::string, std::string>>), override);
};