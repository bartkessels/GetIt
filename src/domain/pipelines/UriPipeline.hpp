#pragma once

#include <memory>
#include <string>

#include "domain/RequestPipeline.hpp"

namespace getit::domain::pipelines
{
    class UriPipeline: public RequestPipeline
    {
        public:
            explicit UriPipeline(std::string uri);
            ~UriPipeline() = default;
    
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;
            void executeAfterRequest(std::shared_ptr<Response> response) override;

        private:
            std::string uri;
    };
}