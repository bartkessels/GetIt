#pragma once

#include <memory>
#include <string>

#include "domain/BeforeRequestPipeline.hpp"

namespace getit::domain::pipelines
{
    class UriPipeline: public BeforeRequestPipeline
    {
        public:
            explicit UriPipeline(std::string uri);
            ~UriPipeline() = default;
    
            /**
             * @brief Set the uri to which the request should be sent
             * 
             * @param data The RequestData object on which the uri is set
             * @return void
             */
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;

        private:
            std::string uri;
    };
}