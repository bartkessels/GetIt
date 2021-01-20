#pragma once

#include <memory>

#include "domain/Response.hpp"

namespace getit::domain
{
    struct AfterRequestPipeline
    {
        public:
            virtual ~AfterRequestPipeline() = default;

            /**
             * @brief Get the Response of the request after the request is sent
             * 
             * @param response the response from the request client
             * @return void
             */
            virtual void executeAfterRequest(std::shared_ptr<Response> response) = 0;
    };
}