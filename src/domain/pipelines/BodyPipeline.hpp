#pragma once

#include <memory>
#include <stdexcept>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestBody.hpp"
#include "domain/RequestData.hpp"
#include "domain/Response.hpp"

namespace getit::domain::pipelines
{
    class BodyPipeline: public BeforeRequestPipeline
    {
        public:
            explicit BodyPipeline(std::shared_ptr<RequestBody> body);
            ~BodyPipeline() = default;

            /**
             * @brief Add the body to the RequestData if a body is available
             * 
             * @param data The RequestData on which the body is added
             * @return void
             */
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;

        private:
            std::shared_ptr<RequestBody> body;
    };
}