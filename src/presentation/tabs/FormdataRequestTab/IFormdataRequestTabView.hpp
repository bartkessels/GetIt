#pragma once

#include <map>
#include <string>

#include "presentation/tabs/RequestTabView.hpp"

namespace getit::presentation::tabs
{
    struct IFormdataRequestTabView: public RequestTabView
    {
        public:
            virtual ~IFormdataRequestTabView() = default;

            virtual void setBoundary(std::string boundary) = 0;
            virtual void setElements(std::map<std::string, std::string> elements) = 0;
            virtual void setFiles(std::map<std::string, std::string> files) = 0;

            virtual void addElement(std::string key, std::string value) = 0;
            virtual void addFile(std::string key, std::string filePath) = 0;

            virtual std::string getBoundary() = 0;
            virtual std::map<std::string, std::string> getElements() = 0;
            virtual std::map<std::string, std::string> getFiles() = 0;
    };
}