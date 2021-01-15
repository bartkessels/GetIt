#pragma once

#include <memory>
#include <string>

#include "domain/RequestPipeline.hpp"

namespace getit::domain::pipelines
{
    class MethodPipeline: public RequestPipeline
    {
        public:
            explicit MethodPipeline(std::string httpMethod);
            ~MethodPipeline() = default;
    
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;
            void executeAfterRequest(std::shared_ptr<Response> response) override;

        private:
            std::string httpMethod;
    };
}