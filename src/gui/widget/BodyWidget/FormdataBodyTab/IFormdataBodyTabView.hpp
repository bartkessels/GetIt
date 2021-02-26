#pragma once

#include <map>
#include <string>

namespace getit::gui::widget::BodyWidget
{
    struct IFormdataBodyTabView
    {
        public:
            ~IFormdataBodyTabView() = default;

            virtual std::map<std::string, std::string> getElements() = 0;
            virtual std::map<std::string, std::string> getFiles() = 0;

            virtual void setElements(std::map<std::string, std::string> elements) = 0;
            virtual void setFiles(std::map<std::string, std::string> files) = 0;
    };
}