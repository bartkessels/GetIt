#pragma once

#include <map>
#include <string>

#include "domain/BeforeRequestPipeline.hpp"

namespace getit::domain::pipelines
{
    class HeadersPipeline: public BeforeRequestPipeline
    {
        public:
            HeadersPipeline() = default;
            ~HeadersPipeline() = default;

            void addHeader(std::string header, std::string value);
            void removeHeader(std::string header);

            /**
             * @brief Add the headers to the request
             * 
             * @param data the RequestData on which the headers are set
             * @return void
             */
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;

        private:
            std::map<std::string, std::string> headers;
    };
}