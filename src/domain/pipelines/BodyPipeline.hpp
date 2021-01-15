#pragma once

#include <memory>

#include "domain/RequestBody.hpp"
#include "domain/RequestData.hpp"
#include "domain/RequestPipeline.hpp"
#include "domain/Response.hpp"

namespace getit::domain::pipelines
{
    class BodyPipeline: public RequestPipeline
    {
        public:
            explicit BodyPipeline(std::shared_ptr<RequestBody> body);
            ~BodyPipeline() = default;

            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;
            void executeAfterRequest(std::shared_ptr<Response> response) override;

        private:
            std::shared_ptr<RequestBody> body;
    };
}