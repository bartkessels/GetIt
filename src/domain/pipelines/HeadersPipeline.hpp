#pragma once

#include "domain/RequestPipeline.hpp"

namespace getit::domain::pipelines
{
    class HeadersPipeline: public RequestPipeline
    {
        public:
            HeadersPipeline() = default;
            ~HeadersPipeline() = default;

            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;
            void executeAfterRequest(std::shared_ptr<Response> response) override;
    };
}