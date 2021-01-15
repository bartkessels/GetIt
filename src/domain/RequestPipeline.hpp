#pragma once

#include <memory>

#include "domain/RequestData.hpp"
#include "domain/Response.hpp"

namespace getit::domain
{
    struct RequestPipeline
    {
        public:
            virtual ~RequestPipeline() = default;

            /**
             * @brief Modify the RequestData before the request is sent
             * 
             * @param data this data will be sent to the request client
             * @return void
             */
            virtual void executeBeforeRequest(std::shared_ptr<RequestData> data) = 0;

            /**
             * @brief Get the Response of the request after the request is sent
             * 
             * @param response the response from the request client
             * @return void
             */
            virtual void executeAfterRequest(std::shared_ptr<Response> response) = 0;
    };
}