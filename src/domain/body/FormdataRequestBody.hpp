#pragma once

#include <boost/format.hpp>
#include <fstream>
#include <list>
#include <string>
#include <utility>

#include "domain/RequestBody.hpp"

namespace getit::domain::body
{
    class FormdataRequestBody: public RequestBody
    {
        public:
            explicit FormdataRequestBody(std::string boundary);
            ~FormdataRequestBody() override = default;

            void addElement(const std::string& key, const std::string& value);
            void addFile(const std::string& key, const std::string& filePath);

            std::string getContentType() override;
            std::string getBody() override;
            size_t getSize() override;

        private:
            std::string buildContentData(const std::string& key, const std::string& value);
            std::string buildContentDataFile(const std::string&, const std::string& fileName, const std::string& contents);

            std::string boundary;
            std::list<std::string> body;
    };
}