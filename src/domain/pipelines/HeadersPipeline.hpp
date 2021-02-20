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

            /**
             * @brief Add the headers to the request
             * 
             * @param data the RequestData on which the headers are set
             * @return void
             */
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;

        private:
            nonUniqueMap headers;
    };
}